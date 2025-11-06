setopt PROMPT_SUBST

alias ll="ls -lh"
alias la="ls -lAh"

alias ..="cd .."
alias .2="cd ../../"
alias .3="cd ../../../"
alias .4="cd ../../../../"

export EDITOR=nano

PROMPT=$'\033[0;38;2;127;127;127;49m%n\033[0;38;5;9;49m@\033[0;39;49m%m:$(basename $(tty) 2>/dev/null) \033[0;38;2;127;155;127;49m%d \033[0;39;49m(\033[0;38;2;200;155;200;49m%?\033[0;39;49m)\n> '