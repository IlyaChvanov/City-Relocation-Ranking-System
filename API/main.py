import subprocess

input_data = "Moscow\nRussia"

process = subprocess.Popen(['..\\cmake-build-debug\\City-Relocation-Ranking-System.exe'],
                           stdin=subprocess.PIPE,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE,
                           text=True)

output, error = process.communicate(input=input_data)

print("Output from C++ program:", output)
if error:
    print("Error:", error)