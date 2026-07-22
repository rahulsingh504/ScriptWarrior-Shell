import tkinter as tk
from subprocess import Popen, PIPE, STDOUT
import threading

class ShellGUI:
    def __init__(self, master):
        self.master = master
        master.title("ScriptWarrior Shell GUI")

        self.text = tk.Text(master, height=24, width=80, bg="black", fg="lime")
        self.text.pack()

        self.entry = tk.Entry(master, width=80)
        self.entry.pack()
        self.entry.bind("<Return>", self.send_command)

        self.proc = Popen(["./main"], stdin=PIPE, stdout=PIPE, stderr=STDOUT, text=True, bufsize=1)
        threading.Thread(target=self.read_output, daemon=True).start()

    def read_output(self):
        while True:
            char = self.proc.stdout.read(1)
            if not char:
                break
            self.text.insert(tk.END, char)
            self.text.see(tk.END)

    def send_command(self, event):
        cmd = self.entry.get() + "\n"
        self.proc.stdin.write(cmd)
        self.proc.stdin.flush()
        self.entry.delete(0, tk.END)

root = tk.Tk()
app = ShellGUI(root)
root.mainloop()