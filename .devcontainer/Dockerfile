ARG VARIANT=ubuntu-21.04
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update
RUN apt-get -y install --no-install-recommends libcpprest-dev libssl-dev
