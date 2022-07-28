using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class UDPReceive : MonoBehaviour
{
    int LOCAL_PORT = 12345;
    static UdpClient udp;
    Thread thread;
    public string parameter;

    public static Action<string> DataCallBack;

    void Start()
    {
        UDPReceive.DataCallBack += Method;
        UDPStart();
    }

    public void UDPStart()
    {

        udp = new UdpClient(LOCAL_PORT);
        thread = new Thread(new ThreadStart(ThreadMethod));

        thread.Start();
    }

    public void Method(string data)
    {
        parameter = data;
    }

    void OnApplicationQuit()
    {
        thread.Abort();
    }

    private static void ThreadMethod()
    {
        while (true)
        {

            IPEndPoint remoteEP = null;
            byte[] data = udp.Receive(ref remoteEP);
            string text = Encoding.ASCII.GetString(data);

            DataCallBack(text);
            Debug.Log(text);
        }
    }
}