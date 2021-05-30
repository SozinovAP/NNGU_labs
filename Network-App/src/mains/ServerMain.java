package mains;

import clock.ServerWork;
import sample.ClockObserver;

import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

class ServerMain {
    int port = 8001;
    InetAddress host;
    ServerWork serverWork = new ServerWork();

    public ServerMain() {

        try {
            host = InetAddress.getLocalHost();
            System.out.println(host);
            System.out.println(port);
        } catch (UnknownHostException ex) {
            Logger.getLogger(ServerMain.class.getName()).log(Level.SEVERE, null, ex);
        }

        try {
            ServerSocket serverSocket = new ServerSocket(port, 0, host);
            System.out.println("Server started");

            while (true) {
                Socket socket = serverSocket.accept();

                System.out.println("client connected");
                ClockObserver clockObserver = new ClockObserver(socket, serverWork);
            }
        } catch (Exception e) {
            Logger.getLogger(ServerMain.class.getName()).log(Level.SEVERE, null, e);
        }

    }

    public static void main(String[] args) {
        new ServerMain();
    }
}
