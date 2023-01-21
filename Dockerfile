FROM gcc:latest

COPY . ./betriebssysteme

WORKDIR /betriebssysteme/

RUN cd /betriebssysteme/

CMD ["tail", "-f", "/dev/null"]