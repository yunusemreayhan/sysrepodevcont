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
RUN /usr/bin/python3 -m venv /repos/.venv

RUN echo "version update 0.0.1"

RUN cd /repos && git clone https://github.com/YangModels/yang.git
RUN cd /repos && git clone https://github.com/yunusemreayhan/yang-analysis.git
RUN cd ~ && git clone --depth=1 https://github.com/amix/vimrc.git ~/.vim_runtime
RUN sh ~/.vim_runtime/install_awesome_vimrc.sh

RUN bash -c "source /repos/.venv/bin/activate && python3 -m pip install --upgrade pip"
RUN bash -c "source /repos/.venv/bin/activate && python3 -m pip install -r /repos/yang-analysis/requirements.txt"
RUN bash -c "echo 'root:1' | chpasswd"

RUN bash -c "git config --global core.autocrlf true"

# RUN bash -c "ls /repos/sysrepo-pg/install-yangs.sh && chmod +x /repos/sysrepo-pg/install-yangs.sh && /repos/sysrepo-pg/install-yangs.sh"