debug:
	g++ -g ./SQL/SqlCon.cpp ./Communi_Core.cpp ./Server_Main.cpp -o Server_Main.out -pthread -lmysqlclient
	g++ -g ./SQL/SqlCon.cpp ./Communi_Core.cpp ./Client_demo.cpp  -pthread -lmysqlclient -o Client_demo.out

client:
	g++ -g ./SQL/SqlCon.cpp ./Communi_Core.cpp ./Client_demo.cpp  -pthread -lmysqlclient -o Client_demo.out

communi:
	g++ -g ./SQL/SqlCon.cpp ./Communi_Core.cpp ./Communi_Client.cpp  -pthread -lmysqlclient -o Communi_Client.out;
	g++ -g ./SQL/SqlCon.cpp ./Communi_Core.cpp ./Communi_Server.cpp  -pthread -lmysqlclient -o Communi_Server.out;
	