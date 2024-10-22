import csv
import os
import sys

file_path = "../raw/fr_seeds.csv"

script_dir = os.path.dirname(os.path.abspath(__file__))
data_dir = os.path.join(script_dir, '..', 'FR')
sys.path.append(data_dir)

audio = ["Stereo", "Mono"]
button_option = ["LA", "LR", "HELP"]
seed_button = ["A", "L", "Start"]

game_options = {
    "Stereo And L=A": [audio[0], button_option[0]],
    "Stereo And Help": [audio[0], button_option[2]],
    "Stereo And LR": [audio[0], button_option[1]],
    "Mono And L=A": [audio[1], button_option[0]],
    "Mono And Help": [audio[1], button_option[2]],
    "Mono And LR": [audio[1], button_option[1]],
}

game_strings = [
    "Stereo And L=A",
    "Stereo And Help",
    "Stereo And LR",
    "Mono And L=A",
    "Mono And Help",
    "Mono And LR"
]

bad_strings = ["", "0000", "#N/A", "#VALUE!"]
opts = []
timer_row = 2
seed_row = 3

for _ in range(14):
    opts.clear()
    headers = []
    with open(file_path, mode='r', encoding="utf-8") as f:
        csv_file = csv.reader(f)
        for row in csv_file:
            if row[seed_row] in game_strings:
                headers.append(game_options[row[seed_row]])
            if row[seed_row] in seed_button:
                headers.append(row[seed_row])
                break
        for _ in range(5):
            next(csv_file, None)
        for row in csv_file:
            if row[seed_row] not in bad_strings:
                entry = [
                    row[timer_row],
                    row[seed_row]
                ]
                opts.append(entry)
    timer_row += 5
    seed_row += 5

    with open(f"{data_dir}//{headers[0][0]}-{headers[0][1]}-{headers[1]}", 'w', newline='\n') as file:
        writer = csv.writer(file)
        writer.writerows(opts)