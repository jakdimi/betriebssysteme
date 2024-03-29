echo "Killing container if it is running:"
docker ps | grep betriebssysteme && docker container kill betriebssysteme
echo "Deleting container if it exists:"
docker ps -a | grep betriebssysteme && docker contianer rm betriebssysteme
echo "Deleting image if it exists:"
docker image ls | grep betriebssysteme && docker image rm betriebssysteme
docker build -t "betriebssysteme" --build-arg blatt=$1 .
docker run --name "betriebssysteme" -d betriebssysteme
sleep 2
docker exec betriebssysteme ls /betriebssysteme/$1 | grep Makefile && docker exec betriebssysteme make --directory /betriebssysteme/$1 all
docker exec -it betriebssysteme /bin/bash
echo "Kill container:"
docker container kill betriebssysteme
echo "Delete container:"
docker container rm betriebssysteme