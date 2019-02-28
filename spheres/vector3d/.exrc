if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <SNR>12_AutoPairsReturn =AutoPairsReturn()
vnoremap 	 =
nnoremap 	 =h
vnoremap <NL> :m '>+1gv=gv
nnoremap <NL> :m .+1==
vnoremap  :m '<-2gv=gv
nnoremap  :m .-2==
vnoremap  c
nnoremap  ciw
nnoremap <silent>  :CtrlP
nnoremap   :
nnoremap ! :!
map - $
nnoremap .m :w:!gcc "%:p" -o "%:p:r.out"
nnoremap .A :ALEEnableBuffer
nnoremap .a :ALEDisableBuffer
nnoremap .D :bd!
nnoremap .d :w:bd
nnoremap .Q :q!
nnoremap .q :q
nnoremap .w :w:q
nnoremap .s :w
nnoremap .r :!clear:!"%:p:r.out"
nnoremap .c :w:!clear:!g++ -std=c++17 "%:p" -o "%:p:r.out"
nnoremap .p :w:!clear:!python "%:p"
nmap ;{ A{
nnoremap ;; $a;
nnoremap ? :nohl
vnoremap H 5h
nnoremap H 5h
vnoremap J 5j
nnoremap J 5j
vnoremap K 5k
nnoremap K 5k
vnoremap L 5l
nnoremap L 5l
nnoremap Q @
xmap S <Plug>VSurround
nnoremap [ {
nnoremap ] }
vmap `` gc
nmap `` gcc
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap ds <Plug>Dsurround
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
xmap gS <Plug>VgSurround
nmap gcu <Plug>Commentary<Plug>Commentary
nmap gcc <Plug>CommentaryLine
omap gc <Plug>Commentary
nmap gc <Plug>Commentary
xmap gc <Plug>Commentary
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
nnoremap { {{{{{
nnoremap } }}}}}
nmap ~ A// 
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
nnoremap <silent> <Plug>SurroundRepeat .
nmap <silent> <Plug>CommentaryUndo :echoerr "Change your <Plug>CommentaryUndo map to <Plug>Commentary<Plug>Commentary"
nnoremap <silent> <Plug>(ale_hover) :ALEHover
nnoremap <silent> <Plug>(ale_find_references) :ALEFindReferences
nnoremap <silent> <Plug>(ale_go_to_definition_in_tab) :ALEGoToDefinitionInTab
nnoremap <silent> <Plug>(ale_go_to_definition) :ALEGoToDefinition
nnoremap <silent> <Plug>(ale_fix) :ALEFix
nnoremap <silent> <Plug>(ale_detail) :ALEDetail
nnoremap <silent> <Plug>(ale_lint) :ALELint
nnoremap <silent> <Plug>(ale_reset_buffer) :ALEResetBuffer
nnoremap <silent> <Plug>(ale_disable_buffer) :ALEDisableBuffer
nnoremap <silent> <Plug>(ale_enable_buffer) :ALEEnableBuffer
nnoremap <silent> <Plug>(ale_toggle_buffer) :ALEToggleBuffer
nnoremap <silent> <Plug>(ale_reset) :ALEReset
nnoremap <silent> <Plug>(ale_disable) :ALEDisable
nnoremap <silent> <Plug>(ale_enable) :ALEEnable
nnoremap <silent> <Plug>(ale_toggle) :ALEToggle
nnoremap <silent> <Plug>(ale_last) :ALELast
nnoremap <silent> <Plug>(ale_first) :ALEFirst
nnoremap <silent> <Plug>(ale_next_wrap) :ALENextWrap
nnoremap <silent> <Plug>(ale_next) :ALENext
nnoremap <silent> <Plug>(ale_previous_wrap) :ALEPreviousWrap
nnoremap <silent> <Plug>(ale_previous) :ALEPrevious
nnoremap <Right> :bnzz
nnoremap <Left> :bpzz
imap S <Plug>ISurround
imap s <Plug>Isurround
inoremap <NL> :m .+1==gi
inoremap  :m .-2==gi
imap  <Plug>Isurround
inoremap ,, cc
inoremap ,. wbcw
imap ;; A;
imap ;{ A{
inoremap Jk 
inoremap JK 
inoremap jK 
inoremap jk 
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=2
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set hidden
set hlsearch
set ignorecase
set laststatus=2
set modelines=0
set operatorfunc=<SNR>15_go
set ruler
set runtimepath=~/.vim,~/.vim/bundle/ale,~/.vim/bundle/auto-pairs,~/.vim/bundle/bufferline,~/.vim/bundle/commentary,~/.vim/bundle/crosshairs,~/.vim/bundle/ctrlp,~/.vim/bundle/lightline,~/.vim/bundle/lightline-bufferline,~/.vim/bundle/monokai-tasty,~/.vim/bundle/surround,/usr/share/vim/vimfiles,/usr/share/vim/vim80,/usr/share/vim/vimfiles/after,~/.vim/after
set shiftwidth=6
set shortmess=filnxtToOI
set noshowmode
set smartindent
set tabline=%!lightline#tabline()
set tabstop=6
set title
set window=0
" vim: set ft=vim :
