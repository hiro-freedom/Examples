" All system-wide defaults are set in $VIMRUNTIME/debian.vim and sourced by
" the call to :runtime you can find below.  If you wish to change any of those
" settings, you should do it in this file (/etc/vim/vimrc), since debian.vim
" will be overwritten everytime an upgrade of the vim packages is performed.
" It is recommended to make changes after sourcing debian.vim since it alters
" the value of the 'compatible' option.

" This line should not be removed as it ensures that various options are
" properly set to work with the Vim-related packages available in Debian.
runtime! debian.vim


filetype off                  " off before Vundle
" Vundle
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

"python auto complete
Plugin 'Valloric/YouCompleteMe'

" Python auto indent
Plugin 'vim-scripts/indentpython.vim'

" Python gramma check
Plugin 'scrooloose/syntastic'

" flake8 style check
Plugin 'nvie/vim-flake8'

" nerdtree
Plugin 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
Plugin 'jistr/vim-nerdtree-tabs'

" nerd tree git
Plugin 'Xuyuanp/nerdtree-git-plugin'

" gruvbox colorscheme
Plugin 'morhetz/gruvbox'

" Python 语言的代码补全
Plugin 'davidhalter/jedi-vim'

"git interface
Plugin 'tpope/vim-fugitive'

" file search
Plugin 'kien/ctrlp.vim'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required


" =======  normal settings  ==========
set nocompatible "关闭与vi的兼容模式
set number " Shows the line numbers
set nowrap    "不自动折行
set showmatch    "显示匹配的括号
set scrolloff=3        "距离顶部和底部3行"
set encoding=utf-8  "编码
set fenc=utf-8      "编码
" set mouse=a " Allow to use the mouse in the editor
set incsearch		" Incremental search
set hlsearch        "搜索高亮
set showcmd		" Show (partial) command in status line.
if has("syntax")
  syntax on
endif
" Jump to the last position when reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif
set backspace=indent,eol,start

set sm!   " 高亮括号
set cursorline " Highlights the current line in the editor
set splitbelow splitright " 分页出现在右侧 下侧
set completeopt=noinsert,menuone,noselect " Modifies the auto-complete menu to behave more like an IDE.
set title " Show file title
set laststatus=2


" ===== scheme & color =====
" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
set background=dark
"colorscheme desert
"colorscheme murphy
colorscheme gruvbox
"set termguicolors


" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.
set autoindent
set tabstop=4
set shiftwidth=4
set noexpandtab
set history=50		" keep 50 lines of command line history
set ruler		" show the cursor position all the time

" Source a global configuration file if available
" if filereadable("/etc/vim/vimrc.local")
"   source /etc/vim/vimrc.local
" endif



" pep8 style for .py
au BufNewFile,BufRead *.py
\ set tabstop=4   "tab宽度
\ set softtabstop=4
\ set shiftwidth=4
\ set textwidth=78  "行最大宽度
\ set expandtab       "tab替换为空格键
\ set autoindent
\ set fileformat=unix   "保存文件格式


" ===== settings of plugins =====
" nerdtree
let NERDTreeIgnore=['\~$', '\.pyc$', '\.swp$']
let NERDTreeQuitOnOpen=1
let NERDTreeChDirMode=1

" kien/ctrlp.vim 
let g:ctrlp_map = '<F3>'
"map <leader>f :CtrlPMRU<CR>
let g:ctrlp_cmd = 'CtrlP'
let g:ctrlp_custom_ignore = {
    \ 'dir':  '\v[\/]\.(git|hg|svn|rvm)$',
    \ 'file': '\v\.(exe|so|dll|zip|tar|tar.gz|pyc)$',
    \ }
let g:ctrlp_working_path_mode=0
let g:ctrlp_match_window_bottom=1
let g:ctrlp_max_height=15
let g:ctrlp_match_window_reversed=0
let g:ctrlp_mruf_max=500
let g:ctrlp_follow_symlinks=1

"map <C-n> :NERDTreeToggle<CR>
map <F2> :NERDTreeToggle<CR>


" ===== cscope =====
if has("cscope")
  set csprg=/usr/bin/cscope
  set csto=1
  set cst
  set nocsverb
		  " add any database in current directory
  if filereadable("cscope.out")
        cs add cscope.out
  endif
  set csverb
endif

" ======== for python ===========

" indent line
Plugin 'Yggdroot/indentLine'
" :IndentLinesToggle

" auto pep8 with F8
Plugin 'tell-k/vim-autopep8'
autocmd FileType python noremap <buffer> <F8> :call Autopep8()<CR>



" use python3 checker in vim-syntastic/syntastic
let g:syntastic_python_python_exec = 'python3'


