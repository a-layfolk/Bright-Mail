default:
	g++ WZC/Dependencies/SqlCon.cpp WZC/Dependencies/My_Json.cpp WZC/Dependencies/Communi_Core.cpp WZC/Server/Server_Core.cpp WZC/Server/Server_Main.cpp -o Server_Main.out -pthread -lmysqlclient;
	g++ WZC/Dependencies/My_Json.cpp WZC/Dependencies/Communi_Core.cpp WZC/Client/Client_Core.cpp WZC/Client/Client_demo.cpp -o Client_demo.out;

client:
	g++ WZC/Dependencies/My_Json.cpp WZC/Dependencies/Communi_Core.cpp WZC/Client/Client_Core.cpp WZC/Client/Client_demo.cpp -o Client_demo.out;

server:
	g++ WZC/Dependencies/SqlCon.cpp WZC/Dependencies/My_Json.cpp WZC/Dependencies/Communi_Core.cpp WZC/Server/Server_Core.cpp WZC/Server/Server_Main.cpp -o Server_Main.out -pthread -lmysqlclient;

server_debug:
	g++ -g WZC/Dependencies/SqlCon.cpp WZC/Dependencies/My_Json.cpp WZC/Dependencies/Communi_Core.cpp WZC/Server/Server_Core.cpp WZC/Server/Server_Main.cpp -o Server_Main.out -pthread -lmysqlclient;

client_debug:
	g++ -g WZC/Dependencies/My_Json.cpp WZC/Dependencies/Communi_Core.cpp WZC/Client/Client_Core.cpp WZC/Client/Client_demo.cpp -o Client_demo.out;