import requests
import csv
import os
import sys

sheets = {
    "English LG": ["12TUcXGbLY_bBDfVsgWZKvqrX13U6XAATQZrYnzBKP6Y", "2091244688"],
    "English FR": ["1Mf3F4kTvNEYyDGWKVmMSiar3Fwh1PLzWVXUvGx9YxfA", "1006198830"]
}

audio = ["Stereo", "Mono"]
button_option = ["LA", "LR", "HELP"]
seed_button = ["A", "L", "Start"]
bad_strings = ["", "0000", "#N/A", "#VALUE!"]

lg_game_strings = [
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
    "MONO/L=A, L",
    "STEREO/L=A, L"
]

fr_game_strings = [
    "Stereo And L=A",
    "Stereo And Help",
    "Stereo And LR",
    "Mono And L=A",
    "Mono And Help",
    "Mono And LR"
]

lg_game_options = {
    lg_game_strings[0]: [audio[1], button_option[1], seed_button[0]],
    lg_game_strings[1]: [audio[1], button_option[0], seed_button[0]],
    lg_game_strings[2]: [audio[1], button_option[2], seed_button[0]],
    lg_game_strings[3]: [audio[0], button_option[1], seed_button[0]],
    lg_game_strings[4]: [audio[0], button_option[0], seed_button[0]],
    lg_game_strings[5]: [audio[0], button_option[2], seed_button[0]],
    lg_game_strings[6]: [audio[1], button_option[1], seed_button[2]],
    lg_game_strings[7]: [audio[1], button_option[0], seed_button[2]],
    lg_game_strings[8]: [audio[1], button_option[2], seed_button[2]],
    lg_game_strings[9]: [audio[0], button_option[1], seed_button[2]],
    lg_game_strings[10]: [audio[0], button_option[0], seed_button[2]],
    lg_game_strings[11]: [audio[0], button_option[2], seed_button[2]],
    lg_game_strings[12]: [audio[1], button_option[0], seed_button[1]],
    lg_game_strings[13]: [audio[0], button_option[0], seed_button[1]],
}

fr_game_options = {
    fr_game_strings[0]: [audio[0], button_option[0]],
    fr_game_strings[1]: [audio[0], button_option[2]],
    fr_game_strings[2]: [audio[0], button_option[1]],
    fr_game_strings[3]: [audio[1], button_option[0]],
    fr_game_strings[4]: [audio[1], button_option[2]],
    fr_game_strings[5]: [audio[1], button_option[1]],
}


def fetch_sheet_data(sheet_id, gid):
    url = f"https://docs.google.com/spreadsheets/d/{sheet_id}/export?format=csv&gid={gid}"
    try:
        response = requests.get(url)
        response.raise_for_status()
        return response.text
    except requests.exceptions.RequestException as e:
        print(e)
        return None


def write_english_fr_data():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'FR')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["English FR"][0], sheets["English FR"][1])

    timer_row = 2
    seed_row = 3
    for _ in range(14):
        opts = []
        headers = []
        csv_file = csv.reader(text.split("\n"), delimiter=",")

        for row in csv_file:
            if row[seed_row] in fr_game_strings:
                headers.append(fr_game_options[row[seed_row]])
            if row[seed_row] in seed_button:
                headers.append(row[seed_row])
                break

        for _ in range(3):
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


def write_english_lg_data():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'LG')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["English LG"][0], sheets["English LG"][1])
    timer_row = 2
    seed_row = 3

    for _ in range(14):
        opts = []
        headers = []
        csv_file = csv.reader(text.split("\n"), delimiter=",")
        next(csv_file, None)
        for row in csv_file:
            if row[seed_row] in lg_game_strings:
                headers = lg_game_options[row[seed_row]]
                break

        for row in csv_file:
            if row[seed_row] not in bad_strings:
                entry = [row[timer_row], row[seed_row]]
                opts.append(entry)
        seed_row += 1

        with open(f"{data_dir}/{headers[0]}-{headers[1]}-{headers[2]}", 'w', newline='\n') as file:
            writer = csv.writer(file)
            writer.writerows(opts)

def main():
    write_english_lg_data()
    write_english_lg_data()


if __name__ == "__main__":
    main()