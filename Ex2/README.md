# Overview

This project includes two programs, ttt and mync, which can be compiled and run using the provided Makefile. The mync program can be run in various modes, using either TCP or UDP protocols, and includes instructions for using Unix domain sockets.

## Compilation

To compile the programs, use the following command:
(Copy code)
make all
This will compile the ttt and mync programs.

## Running the Programs

### TCP Mode

#### Interactive Mode (-i)
1.	First terminal:
(Copy code)
./mync -e "ttt 123456789" -i TCPS4050
2.	Second terminal:
	(Copy code)
nc localhost 4050

#### Input and Output Mode (-i -o)

1.	First terminal:
(Copy code)
nc -l 4455
2.	Second terminal:

	(Copy code)
./mync -e "./ttt 123456789" -i TCPS4050 -o TCPClocalhost,4455
3.	Third terminal:
(Copy code)
nc localhost 4050

#### Background Mode (-b)
1.	First terminal:
(Copy code)
./mync -e "./ttt 123456789" -b TCPS4050
2.	Second terminal:
(Copy code)
nc localhost 4050

### UDP Mode

#### Interactive Mode (-i)

1.	First terminal:
Copy code
./mync -e "ttt 123456789" -i UDPS4050
2.	Second terminal:
Copy code
nc -u localhost 4050

#### Input (UDP) and Output (TCP) Mode (-i (udp) -o (tcp))
1.	First terminal:
(Copy code)
nc -l 4455
2.	Second terminal:
(Copy code)
./mync -e "ttt 123456789" -i UDPS4050 -o TCPClocalhost,4455
3.	Third terminal:
(Copy code)
nc -u localhost 4050

#### Input (UDP) and Output (UDP) Mode (-i (udp) -o (udp))

1.	First terminal:
(Copy code)
nc -u -l 4455
2.	Second terminal:
(Copy code)
./mync -e "ttt 123456789" -i UDPS4050 -o UDPClocalhost,4455
3.	Third terminal:
(Copy code)
nc -u localhost 4050

### Unix Domain Sockets Mode

****************************Modify Path******************************
For the following commands there is need in modification of path to the location of "mysocket" file on your computer.
Please change path to your "mysocket" file below some help of how to do it.


Instructions for changing path:
1.Right click on "mysocket" file.
2. In options click on copy path.
3.Replace path -    "./mync -e "./ttt 123456789" -i UDSSS/home/elioz/Operating_Systems/Ex2/exe6/mysocket
" for example if your path:
"/home/AhlaMartze/Operating_Systems/Ex2/exe6/mysocket "
The new command will be:
"./mync -e "./ttt 123456789" -i UDSSS/ home/AhlaMartze/Operating_Systems/Ex2/exe6/mysocket "

Ensure you updated the path to "mysocket" to match its location on your computer.

#### Interactive Mode (-i and -o)

**TCP Case**

1.	First terminal (UDSSS):
(Copy code and change path)
./mync -e "./ttt 123456789" -i UDSSS/home/elioz/Operating_Systems/Ex2/exe6/mysocket
2.	Second terminal (UDSCS):
(Copy code and change path)
./mync -o UDSCS/home/elioz/Operating_Systems/Ex2/exe6/mysocket
**UDP Case**
1.	First terminal (UDSSD):
(Copy code and change path)
./mync -e "./ttt 123456789" -i UDSSD/home/elioz/Operating_Systems/Ex2/exe6/mysocket
2.	Second terminal (UDSCD):
(Copy code and change path)
./mync -o UDSCD/home/elioz/Operating_Systems/Ex2/exe6/mysocket

#### Background Mode (-b)

Only for TCP.

1.	First terminal:
(Copy code and change path)
./mync -e "./ttt 123456789" -b UDSSS/home/elioz/Operating_Systems/Ex2/exe6/mysocket
2.	Second terminal:
(Copy code and change path)
./mync -e "./ttt 123456789" -b UDSCS/home/elioz/Operating_Systems/Ex2/exe6/mysocket

### Code Coverage

To calculate code coverage, use the following command after running the program:
(Copy code)
make coverage

### Cleaning Up

To remove compiled files and coverage data, use the following command:
(Copy code)
make clean

### Notes

To kill any process using a specific port (e.g., port 8080), use the following command:
(Copy code)
sudo kill $(lsof -t -i:8080)

