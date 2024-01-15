// winsnmp_example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Winsnmp.h> 


SNMPAPI_STATUS CALLBACK cbFunc 
(HSNMP_SESSION hSession, HWND hWnd, UINT wMsg, 
WPARAM wParam, LPARAM lParam, LPVOID lpClientData) 
{ // This is a noop function for this app, but must be present. 
    HSNMP_PDU hRecvPdu;
	HSNMP_ENTITY hRecvDst; 
	HSNMP_ENTITY hRecvSrc; 
	smiUINT32 lStat; 
 
	lStat = SnmpRecvMsg(hSession, &hRecvSrc, &hRecvDst, NULL, &hRecvPdu);
    if (lStat != SNMPAPI_SUCCESS ) {
		lStat = SnmpGetLastError(hSession);
		printf ("SnmpRecvMsg() failed:\n" ); 
    }
 
    smiINT pduType = 0;
    HSNMP_VBL vbl;
    SnmpGetPduData(hRecvPdu, &pduType, NULL, NULL, NULL, &vbl);
 
    smiOID oid;
    smiVALUE value;
    SnmpGetVb(vbl, 1, &oid, &value);
 
    char strOid[256] = { 0 };
    SnmpOidToStr(&oid, 256, strOid);
 
    //QVariant data;
    //switch (value.syntax) {
    //case SNMP_SYNTAX_NULL:
    //case SNMP_SYNTAX_NOSUCHOBJECT:
    //case SNMP_SYNTAX_NOSUCHINSTANCE:
    //case SNMP_SYNTAX_ENDOFMIBVIEW:
    //    data = QVariant(QVariant::Invalid);
    //    break;
    //case SNMP_SYNTAX_OCTETS:
    //case SNMP_SYNTAX_BITS:
    //case SNMP_SYNTAX_OPAQUE:
    //case SNMP_SYNTAX_IPADDR:
    //case SNMP_SYNTAX_NSAPADDR:
    //    data = QVariant(QByteArray(reinterpret_cast<const char *>(value.value.string.ptr),
    //                               static_cast<int>(value.value.string.len)));
    //    break;
    //case SNMP_SYNTAX_INT:
    //case SNMP_SYNTAX_UINT32:
    //case SNMP_SYNTAX_CNTR32:
    //case SNMP_SYNTAX_GAUGE32:
    //case SNMP_SYNTAX_TIMETICKS:
    //case SNMP_SYNTAX_CNTR64:
    //    data = QVariant(static_cast<qulonglong>(value.value.sNumber));
    //    break;
    //default:
    //    break;
    //}
 
    SnmpFreeDescriptor(value.syntax, &value.value.string);
    SnmpFreePdu(hRecvPdu);
    SnmpFreeVbl(vbl);
	return (SNMPAPI_SUCCESS); 
} 

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD nTime1=0, nTime2=0; 
	HSNMP_SESSION hSession; 
	HSNMP_ENTITY hDst; 
	HSNMP_CONTEXT hContext; 
	HSNMP_VBL hVbl; 
	HSNMP_PDU hPdu; 
	SNMPAPI_CALLBACK cB = &cbFunc; 
	smiOCTETS dContext = {6, (unsigned char *)"public"}; 

	smiUINT32 lStat; 
	smiUINT32 sysUpTime[] = {1,3,6,1,2,1,1,3,0}; 
	smiUINT32 snmpTrapOid[] = {1,3,6,1,6,3,1 ,1,4,1,0}; 
	smiUINT32 trapValue[] = {1,3,6,1,4,1,12,1,1,1,210}; 

	smiOID dSysUpTimeName = {9, sysUpTime}; 
	smiOID dTrapName = {11, snmpTrapOid}; 
	smiOID dTrapName2 = {11, trapValue}; 

	smiVALUE valSysUpTime; 
	smiVALUE valTrap; 
	smiVALUE valTrap2; 

	lStat = SnmpStartup (&lStat, &lStat, &lStat, &lStat, &lStat); 
	if (lStat == SNMPAPI_FAILURE) 
		return (0); // exit 
	lStat = SnmpSetRetransmitMode(SNMPAPI_ON); 
	hSession = SnmpCreateSession(NULL, 0, cB, NULL); 

	if (hSession == SNMPAPI_FAILURE) 
	{ 
		printf ("SnmpCreateSession() failed!\n"); 
		lStat = SnmpClose (hSession); 
		lStat = SnmpCleanup (); 
		return (0); 
	} 

	lStat = SnmpSetTranslateMode (SNMPAPI_UNTRANSLATED_V1); //SNMPAPI_UNTRANSLATED_V1 

	//THIS IS THE IPADRESS OF SERVER WHERE IS INSTALLER SNMP PROGRAM
	hDst = SnmpStrToEntity (hSession, "192.168.98.82"); 
	if( hDst == SNMPAPI_FAILURE )
	{
		lStat = SnmpGetLastError(hSession);
		return 0;
	}
	//lStat = SnmpSetPort (hDst, 162); 

	hContext = SnmpStrToContext(hSession, &dContext); 
	hVbl = SnmpCreateVbl (hSession, NULL, NULL); 

	valSysUpTime.syntax = SNMP_SYNTAX_TIMETICKS; 
	valSysUpTime.value.uNumber = GetTickCount() / 10; 
	lStat = SnmpSetVb (hVbl, 0, &dSysUpTimeName, &valSysUpTime); 

	//valTrap.syntax = SNMP_SYNTAX_OID; 
	//valTrap.value.oid.len = 11; 
	//valTrap.value.oid.ptr = trapValue; 
	//lStat = SnmpSetVb (hVbl, 0, &dTrapName, &valTrap); 

	//valTrap2.syntax = SNMP_SYNTAX_INT; 
	//valTrap2.value.sNumber = 210; 
	//lStat = SnmpSetVb (hVbl, 0, &dTrapName2, &valTrap2); 

	hPdu = SnmpCreatePdu (hSession, SNMP_PDU_GETNEXT, 0, 0, 0, hVbl); 

	nTime1 = GetTickCount(); 
	lStat = SnmpSendMsg (hSession, NULL, hDst, hContext, hPdu); 
	if (lStat != SNMPAPI_SUCCESS) 
	{ 
		lStat = SnmpGetLastError(hSession);
		printf ("SnmpSendMsg() failed:\n" ); 
	} 

	nTime2 = GetTickCount(); 
	printf ("Elapsed time (in milliseconds): %u \n", nTime2 - nTime1); 


 

	Sleep( 5000 );

	// clean up
	lStat = SnmpFreeContext(hContext); 
	lStat = SnmpClose (hSession); 
	lStat = SnmpCleanup (); 

	return 0; 

}

