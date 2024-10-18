import csv

file_path = "lg_seeds.csv"

audio = ["Stereo", "Mono"]
button_option = ["LA", "LR", "HELP"]
seed_button = ["A", "L", "Start"]

bad_strings = ["", "0000", "#N/A", "#VALUE!"]

game_strings = [
    "MONO/LR",
    "MONO/L=A",
    "MONO/HELP",
    "STEREO/LR",
    "STEREO/L=A",
    "STEREO/HELP",
    "MONO/LR, Start",
    "MONO/L=A, Start",	
    "MONO/HELP, Start",	
    "STEREO/LR, Start",	
    "STEREO/L=A, Start",
    "STEREO/HELP, Start",
]
game_options = {
    game_strings[0] : [audio[1], button_option[1], seed_button[0]],
    game_strings[1] : [audio[1], button_option[0], seed_button[0]],
    game_strings[2] : [audio[1], button_option[2], seed_button[0]],
    game_strings[3] : [audio[0], button_option[1], seed_button[0]],
    game_strings[4] : [audio[0], button_option[0], seed_button[0]],
    game_strings[5] : [audio[0], button_option[2], seed_button[0]],
    game_strings[6] : [audio[1], button_option[1], seed_button[2]],
    game_strings[7] : [audio[1], button_option[0], seed_button[2]],	
    game_strings[8] : [audio[1], button_option[2], seed_button[2]],	
    game_strings[9] : [audio[0], button_option[1], seed_button[2]],	
    game_strings[10]: [audio[0], button_option[0], seed_button[2]],
    game_strings[11]: [audio[0], button_option[2], seed_button[2]],
}

opts = []
timer_row = 2
seed_row = 3
for _ in range(12):
    opts.clear()
    headers = []
    with open(file_path, mode='r', encoding="utf-8") as f:
        csv_file = csv.reader(f)
        next(csv_file, None)
        for row in csv_file:
            if row[seed_row] in game_strings:
                headers = game_options[row[seed_row]]
                break
        
        next(csv_file, None)

        for row in csv_file:
            if row[seed_row] not in bad_strings:
                entry = [row[timer_row], row[seed_row]]
                opts.append(entry)
    seed_row += 1

    with open(f"LG/{headers[0]}-{headers[1]}-{headers[2]}", 'w', newline='\n') as file:
        writer = csv.writer(file)
        writer.writerows(opts)