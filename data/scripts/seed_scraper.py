import requests
import csv
import os
import sys

sheets = {
    "ENG LG": ["12TUcXGbLY_bBDfVsgWZKvqrX13U6XAATQZrYnzBKP6Y", "2091244688"],
    "ENG FR": ["1Mf3F4kTvNEYyDGWKVmMSiar3Fwh1PLzWVXUvGx9YxfA", "1006198830"],
    "EU FR": ["1ZSijzpgauwmlyJATgtNQ16DHKM5Ez9CMbLj-6CHILLw", "282435957"],
    "EU LG": ["1ztCL6eYezqgP_3JrpNOdtsVZGKqU1Lly1SG7gSC75nY", "282435957"],
    "JPN FR 1.0": ["1GMRFM1obLDcYbR6GR6KrE8UZotA7djUTw8PxqVFnCVY", "1608943801"],
    "JPN FR 1.1": ["1aQeWaZSi1ycSytrNEOwxJNoEg-K4eItYagU_dh9VIeU", "791743105"],
    "JPN LG": ["1LSRVD0_zK6vyd6ettUDfaCFJbm00g451d8s96dqAbA4", "1862478029"]
}

audio = ["Stereo", "Mono"]
button_option = ["LA", "LR", "HELP"]
seed_button = ["A", "L", "Start"]
bad_strings = ["", "0000", "#N/A", "#VALUE!", "????"]

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


def adv2ms(advances):
    # NDS frame rate
    return int(round((1 / 59.6555) * 1000 * advances))


def fetch_sheet_data(sheet_id, gid):
    url = f"https://docs.google.com/spreadsheets/d/{sheet_id}/export?format=csv&gid={gid}"
    try:
        response = requests.get(url)
        response.raise_for_status()
        return response.text
    except requests.exceptions.RequestException as e:
        print(e)
        return None


def write_jpn_lg_data():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'LG//JPN')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["JPN LG"][0], sheets["JPN LG"][1])
    timer_row = 0
    seed_row = 1

    for _ in range(5):
        opts = []
        headers = []
        csv_file = csv.reader(text.split("\n"), delimiter=",")
        next(csv_file, None)
        next(csv_file, None)
        for row in csv_file:
            if row[seed_row] in lg_game_strings:
                headers = lg_game_options[row[seed_row]]
                break

        for row in csv_file:
            if row[seed_row] not in bad_strings and row[timer_row] != '':
                timer = adv2ms(int(row[timer_row]))
                entry = [str(timer), row[seed_row]]
                opts.append(entry)
        seed_row += 1

        with open(f"{data_dir}/{headers[0]}-{headers[1]}-{headers[2]}", 'w', newline='\n') as file:
            writer = csv.writer(file)
            writer.writerows(opts)


def write_jpn10_fr_data():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'FR//JPN1_0')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["JPN FR 1.0"][0], sheets["JPN FR 1.0"][1])
    timer_row = 0
    seed_row = 1

    for _ in range(5):
        opts = []
        headers = []
        csv_file = csv.reader(text.split("\n"), delimiter=",")
        next(csv_file, None)
        next(csv_file, None)
        for row in csv_file:
            if row[seed_row] in lg_game_strings:
                headers = lg_game_options[row[seed_row]]
                break

        for row in csv_file:
            if row[seed_row] not in bad_strings and row[timer_row] != '':
                timer = adv2ms(int(row[timer_row]))
                entry = [str(timer), row[seed_row]]
                opts.append(entry)
        seed_row += 1

        with open(f"{data_dir}/{headers[0]}-{headers[1]}-{headers[2]}", 'w', newline='\n') as file:
            writer = csv.writer(file)
            writer.writerows(opts)


def write_jpn11_fr_data():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'FR//JPN1_1')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["JPN FR 1.1"][0], sheets["JPN FR 1.1"][1])
    timer_row = 0
    seed_row = 1

    for _ in range(5):
        opts = []
        headers = []
        csv_file = csv.reader(text.split("\n"), delimiter=",")
        next(csv_file, None)
        next(csv_file, None)
        for row in csv_file:
            if row[seed_row] in lg_game_strings:
                headers = lg_game_options[row[seed_row]]
                break

        for row in csv_file:
            if row[seed_row] not in bad_strings and row[timer_row] != '':
                timer = adv2ms(int(row[timer_row]))
                entry = [str(timer), row[seed_row]]
                opts.append(entry)
        seed_row += 1

        with open(f"{data_dir}/{headers[0]}-{headers[1]}-{headers[2]}", 'w', newline='\n') as file:
            writer = csv.writer(file)
            writer.writerows(opts)


def write_english_fr_data():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'FR//ENG')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["ENG FR"][0], sheets["ENG FR"][1])

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
    data_dir = os.path.join(script_dir, '..', 'LG//ENG')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["ENG LG"][0], sheets["ENG LG"][1])
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


def write_eu_lg_data():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'LG//EU')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["EU LG"][0], sheets["EU LG"][1])
    timer_row = 2
    seed_row = 3

    for _ in range(12):
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


def write_eu_fr_data():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'FR//EU')
    sys.path.append(data_dir)

    text = fetch_sheet_data(sheets["EU FR"][0], sheets["EU FR"][1])
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
    write_english_fr_data()
    write_english_lg_data()
    write_jpn11_fr_data()
    write_jpn10_fr_data()
    write_jpn_lg_data()
    write_eu_lg_data()
    write_eu_fr_data()


if __name__ == "__main__":
    main()
