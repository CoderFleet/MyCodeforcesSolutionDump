import argparse
import os
import sys
import time

import requests

try:
    import cloudscraper
except Exception:
    cloudscraper = None


def build_headers(contest_slug: str) -> dict[str, str]:
    return {
        "User-Agent": (
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
            "AppleWebKit/537.36 (KHTML, like Gecko) "
            "Chrome/120.0.0.0 Safari/537.36"
        ),
        "Accept": "application/json, text/plain, */*",
        "Accept-Language": "en-US,en;q=0.9",
        "Referer": f"https://leetcode.com/contest/{contest_slug}/ranking/",
    }


def fetch_page(
    session: requests.Session,
    contest_slug: str,
    page: int,
    timeout: int,
) -> dict:
    url = f"https://leetcode.com/contest/api/ranking/{contest_slug}/"
    params = {"pagination": page, "region": "global"}
    response = session.get(url, params=params, timeout=timeout)
    response.raise_for_status()
    return response.json()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Fetch LeetCode contest ranking pages and print users up to a rank cutoff.",
    )
    parser.add_argument(
        "contest",
        nargs="?",
        default="weekly-contest-493",
        help="Contest slug, e.g. weekly-contest-493",
    )
    parser.add_argument("--max-rank", type=int, default=4000, help="Maximum rank to print")
    parser.add_argument("--max-pages", type=int, default=160, help="Maximum pages to scan")
    parser.add_argument("--timeout", type=int, default=15, help="HTTP timeout in seconds")
    parser.add_argument(
        "--use-cloudscraper",
        action="store_true",
        help="Use cloudscraper client (useful when requests gets blocked by Cloudflare)",
    )
    parser.add_argument(
        "--sleep",
        type=float,
        default=0.0,
        help="Delay in seconds between requests (helps avoid rate limiting)",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()

    lc_session = os.getenv("LEETCODE_SESSION", "").strip()
    cookies = {"LEETCODE_SESSION": lc_session} if lc_session else {}

    if args.use_cloudscraper:
        if cloudscraper is None:
            print(
                "cloudscraper is not installed. Install it with: pip install cloudscraper",
                file=sys.stderr,
            )
            return 1
        session = cloudscraper.create_scraper(
            browser={"browser": "chrome", "platform": "darwin", "mobile": False}
        )
    else:
        session = requests.Session()

    session.headers.update(build_headers(args.contest))
    if cookies:
        session.cookies.update(cookies)

    total_printed = 0
    for page in range(1, args.max_pages + 1):
        try:
            data = fetch_page(session, args.contest, page, args.timeout)
        except requests.RequestException as exc:
            print(f"Page {page}: request failed ({exc}). Stopping.", file=sys.stderr)
            return 1
        except ValueError as exc:
            print(f"Page {page}: invalid JSON response ({exc}). Stopping.", file=sys.stderr)
            return 1

        rows = data.get("total_rank") or []
        if not rows:
            print(f"Page {page}: no more data.", file=sys.stderr)
            break

        for user in rows:
            rank = user.get("rank")
            username = user.get("username", "")

            if not isinstance(rank, int):
                continue
            if rank > args.max_rank:
                print(f"Reached rank cutoff ({args.max_rank}) at page {page}.", file=sys.stderr)
                print(f"Total printed: {total_printed}", file=sys.stderr)
                return 0

            print(rank, username)
            total_printed += 1

        if args.sleep > 0:
            time.sleep(args.sleep)

    print(f"Completed scan. Total printed: {total_printed}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())