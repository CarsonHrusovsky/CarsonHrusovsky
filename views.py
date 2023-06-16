from base64 import urlsafe_b64decode
from xml.etree import ElementTree as ET
from lib.cuckoo.common.config import Config

from django.shortcuts import render

web_cfg = Config("web")

try:
    import libvirt
except ImportError:
    print("Missed python-libvirt. Use extra/poetry_libvirt_installer.sh")

def index(request, task_id, session_data):
    machines_and_ports = web_cfg.guacamole.labels_and_ports
    machine_list = machines_and_ports.split()
    machine_pairings = []
    machine_pairings = [item.split(":") for item in machine_list]
    labelSize = len(machine_pairings)
    vncport = 0
    try:
        session_id, label, guest_ip = urlsafe_b64decode(session_data).decode("utf8").split("|")
        recording_name = f"{task_id}_{session_id}"
        for x in range(labelSize):
            if (label == machine_pairings[x][0]):
                vncport = int(machine_pairings[x][1])
        if (vncport == 0):
            print("======================")
            print(label)
            print(machine_pairings[x][0])
            print("Machine Label not found. Check configuration within /opt/CAPEv2/custom/conf/web.conf and ensure the name is provided there correctly. Expected format is VirtualMachineName:VNCPortNumber.")
            print("======================")
    except Exception as e:
        return render(
            request,
            "guac/error.html",
            {"error_msg": f"{e}", "error": "remote session", "task_id": task_id},
        )
    return render(
        request,
        "guac/index.html",
           {
                "vncport": vncport,
                "session_id": session_id,
                "task_id": task_id,
                "recording_name": recording_name,
                "guest_ip": guest_ip,
            },
        )
