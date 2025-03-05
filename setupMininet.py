#!/usr/bin/env python3
from mininet.net import Mininet
from mininet.node import OVSBridge
from mininet.cli import CLI
from mininet.log import setLogLevel, info

def myTopology():
    #Creates a mininet topology with 6 hosts and 2 switches

    net = Mininet(topo=None, build=False, ipBase='10.0.0.0/8')

    #print("debugging")
    #create switches
    s1 = net.addSwitch('s1', cls=OVSBridge)
    s2 = net.addSwitch('s2', cls=OVSBridge)

    #create hosts
    h1 = net.addHost('h1', ip='10.0.0.1')
    h2 = net.addHost('h2', ip='10.0.0.2')
    h3 = net.addHost('h3', ip='10.0.0.3')
    h4 = net.addHost('h4', ip='10.0.0.4')
    h5 = net.addHost('h5', ip='10.0.0.5')
    h6 = net.addHost('h6', ip='10.0.0.6')

    #create links
    net.addLink(h1, s1)
    net.addLink(h2, s1)
    net.addLink(h3, s1)
    net.addLink(h4, s1)
    net.addLink(h5, s2)
    net.addLink(h6, s2)

    info('*** Printing links\n')
    for link in net.links:
        info(str(link)+'\n')

    net.start()#Start network
    CLI(net)#run CLI
    net.stop()#Stop network

if __name__ == '__main__':
    setLogLevel('info')
    myTopology()

    
