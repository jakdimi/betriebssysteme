FROM gcc:latest

COPY . ./betriebssysteme

ARG blatt=""
WORKDIR /betriebssysteme/$blatt

RUN apt update \
  && apt upgrade \
  && apt install --assume-yes vim

CMD ["tail", "-f", "/dev/null"]