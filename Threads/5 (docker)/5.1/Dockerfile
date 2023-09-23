FROM ubuntu:16.04
	LABEL maintainer = vladislavtsvetkov2016@yandex.ru
	RUN apt-get update && apt-get install -y g++ nano net-tools inetutils-ping
	WORKDIR /root/test/
	COPY HW.cpp .
	RUN g++ HW.cpp -o HW
	CMD ["./HW"]
