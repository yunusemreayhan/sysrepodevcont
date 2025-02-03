FROM sysrepo/sysrepo-netopeer2

RUN apt update -y
RUN apt install git -y
RUN apt install build-essential -y
RUN apt install clangd -y
RUN apt install cmake -y
RUN apt install neovim -y
RUN apt install vim -y
RUN apt install tmux -y
RUN apt install python3 -y
RUN apt install python3-pip -y
RUN apt install python3-venv -y
RUN apt install gdb -y
RUN apt install valgrind -y

RUN echo "version update 0.0.1"

RUN cd ~ && git clone --depth=1 https://github.com/amix/vimrc.git ~/.vim_runtime
RUN sh ~/.vim_runtime/install_awesome_vimrc.sh

RUN mkdir -p /repos/sysrepodevcont
WORKDIR /repos/sysrepodevcont
