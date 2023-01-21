FROM gcc:latest

COPY . ./betriebssysteme

ARG blatt=""
WORKDIR /betriebssysteme/$blatt
RUN cd /betriebssysteme/$blatt

CMD ["tail", "-f", "/dev/null"]