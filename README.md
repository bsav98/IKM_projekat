## Wireshark

Wireshark je softver za analizu mrežnog saobraćaja. To je alat koji hvata različite mrežne pakete i detaljno ih razlaže. Kada se ovi paketi razbiju, možemo ih koristiti za analizu u realnom vremenu ili van mreže.
Za instalaciju Wireshark softvera potrebno je ispratiti korake na [link]https://www.geeksforgeeks.org/how-to-install-and-use-wireshark-on-ubuntu-linux/)
Na slici ispod je prikazan segment Modbus TCP komunikacije u Wireshark-u
![image](https://user-images.githubusercontent.com/127748379/228214315-6a60780d-274e-45c9-83d3-5aa5ef63a6a2.png)

Modbus TCP je siguran protokol koji omogucava **klijent-server** komunikaciju izmedju uredjaja povezanih na fizicku mrezu(Ethernet).Prije prenosa podataka zahtijeva potvrdu o uspostavljanju konekcije, tako da u Wireshark-u vidimo cetiri poruke:\
 **Modbus Request**- klijent salje zahtjev serveru za uspostavljanje konekcije, vrsi se sinhronizacija obije strane\
 **Modbus Indication**- server prima zahtjev za uspostavljanje konekcije \
 **Modbus Response**- server salje potvrdu(ACK) o primljenoj poruci \
 **Modbus Confirmation**- klijent prima potvrdu sa strane servera, te se uspostavlja konekcija i pocinje prenos podataka
