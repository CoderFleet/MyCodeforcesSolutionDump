import os
import time
from pathlib import Path

import cloudscraper

contest = "biweekly-contest-183"
max_rank = 1000000
output_path = Path("biweekly_183_all_users.txt")
temp_path = output_path.with_suffix(".txt.tmp")

scraper = cloudscraper.create_scraper(browser={"browser": "chrome", "platform": "darwin", "mobile": False})
count = 0

with temp_path.open("w", encoding="utf-8") as file_handle:
    for page in range(1, 800):
        url = f"https://leetcode.com/contest/api/ranking/{contest}/?pagination={page}&region=global"
        response = scraper.get(url, timeout=25)
        response.raise_for_status()
        data = response.json()
        rows = data.get("total_rank") or []
        if not rows:
            print(f"stopped: no rows at page={page}")
            break

        stop = False
        for user in rows:
            rank = user.get("rank")
            username = user.get("username", "")
            if isinstance(rank, int) and rank <= max_rank:
                file_handle.write(f"{rank} {username}\n")
                count += 1
            elif isinstance(rank, int) and rank > max_rank:
                stop = True
                break

        if stop:
            print(f"stopped: reached rank cutoff at page={page}")
            break

        time.sleep(0.08)

os.replace(temp_path, output_path)
print(f"written={count} file={output_path}")
