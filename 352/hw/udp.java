// Java UDP sample code
// Paul Krzyzanowski
// 
// with examples of extracting bits and 16-bit shorts

import java.io.*;
import java.nio.*;	// for ByteBuffer, ByteOrder
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class udp {

	public static void main(String args[]) {

		try {
			int port = 1299;
			byte[] buf = new byte[2048];

			DatagramSocket ds = new DatagramSocket(port);
			DatagramPacket p = new DatagramPacket(buf, buf.length);

			System.out.println("the native byte order is " +
				((ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN) ? "big" : "little")
				+ " endian");

			while (true) {

				System.out.println("waiting on port " + port);
				ds.receive(p);	// wait for a datagram

				System.out.println("received " + p.getLength() +
					" bytes from " + p.getAddress().getHostName());

				examine(p.getData(), p.getLength());

				// echo the packet back to the requestor
				ds.send(p);
			}
		} catch (Exception e) {
			System.err.println(e);
		}
	}

	// take a look at the received packet 

	static void examine(byte[] pbuf, int plen) {

		// dump what we have for debugging
		// a line of hex first, then a line of characters (where possible)

		System.out.println("Received: " + plen + " bytes: ");
		for (int i=0; i < plen; i++)
			System.out.print(String.format("%02x ", pbuf[i]));
		System.out.println("");
		for (int i=0; i < plen; i++)
			if ((pbuf[i] <= ' ') || (pbuf[i] > '~'))
				System.out.print(String.format("%02x ", pbuf[i]));
			else
				System.out.print(String.format("%c  ", pbuf[i]));
		System.out.println("");

		// look at the bytes as big endian shorts
		// the wrap() method uses an existing byte array for the buffer

		short[] shorts = new short[plen/2];
		ByteBuffer.wrap(pbuf).order(ByteOrder.BIG_ENDIAN).asShortBuffer().get(shorts);

		// dump our buffer as shorts
		for (int i=0; i < plen/2; i++)
			System.out.println("short[" + i + "] = " + shorts[i]);

		// another way we can create shorts is by manually putting 2 bytes together
		// internet format is big endian - the first byte has the more significant value
		// this one produces an unsigned result

		int short_value = ((pbuf[0] & 0xff) << 8) + (pbuf[1] & 0xff);
		System.out.println("first 16 bits = " + short_value);


		// demo of extracting bit fields (e.g., for dns)
		// grab the second group of two bytes and treat it as a 16 bit set of bits
		// bits are indexed left to right
		int v = (pbuf[2] & 0xff) << 8 | (pbuf[3] & 0xff);
		for (int i=0; i < 16; i++) {
			System.out.println("bit[" + i + "] = " + (v>>(15-i) & 1));
			// System.out.println("bit[" + i + "] = " + (v & 1<<(15-i)));
		}

		// for example qr, query/response = bit 0 
		boolean qr = ((v >> 15-0) & 1) == 1;
		System.out.println("qr = " + qr);

		// for example rd, recursion desired = bit 7
		boolean rd = ((v >> 15-7) & 1) == 1;
		System.out.println("rd = " + rd);

		// example of setting a bit. Let's set qr to 1
		v |= (1<<(15-0));
		// write v back to the packet buffer
		pbuf[2] = (byte) ((v >> 8) & 0xff);
		pbuf[3] = (byte) (v & 0xff);
	}
}
