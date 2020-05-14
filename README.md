Network Malware Showcase


Erste Schritte nach Starten der VMs:
Als Administrator muss die Powershell geöffnet werden, zum Beispiel einfach über die Taskleiste
1. Test, ob Opfer und Wirt sich erreichen können:
> ping opfer-vm   und 
> ping wirt-vm

2. Firewall ausschalten
> netsh advfirewall set allprofiles state off

3. Auf der Wirt-vm:
    - Drücke Windows-Taste + R und gib ein: "gpedit.msc"
    - Navigiere “Local Computer Policy > Computer Configuration > Administrative Templates > Windows Components > Windows Remote Management (WinRM) > WinRM Client”
    - Unter Trusted Hosts setze  “Trust the remote machine” auf "Enable" und bei "TrustedHostList" schreibe "*" hinein.
    
    Auf der Opfer-vm:
    - Drücke Windows-Taste + R und gib ein: "gpedit.msc"
    - Navigiere “Local Computer Policy > Computer Configuration > Administrative Templates > Windows Components > Windows Remote Management (WinRM) > WinRM 
    -
    -
    - In die Powershell: 
      > Set-Item wsman:\localhost\client\trustedhosts * -Force
      
    
