from ubuntu:15.10

RUN		apt-get update; apt-get -y upgrade

RUN		apt-get install -y  \
			checkinstall \
			make \
			g++ \
			tar \
			wget \
			; \
		wget https://cmake.org/files/v3.5/cmake-3.5.2.tar.gz && \
		tar xf cmake-3.5.2.tar.gz && cd cmake-3.5.2; \
		./configure && make && checkinstall

RUN		apt-get install -y \
			git

COPY		CMakeLists.txt /app/
COPY		src/ /app/src/
WORKDIR	    	/app/

RUN		mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release ../ ; \
		cd - && \
		cmake --build build/ --target zappy -- -j 4

EXPOSE		4243
EXPOSE		4242

CMD		./build/zappy -p 4242 -P 4243 -x 4 -y 4 -c 10 -t 50 -n team1 team2