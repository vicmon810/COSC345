import requests
import json

API_KEY = "712dd084"

with open("id.txt", "r") as file:
    file_content = file.read()

# Open the output file in write mode
with open("poster_links.txt", "w") as output_file:
    for IMDB_ID in file_content.splitlines():
        # Construct the URL
        url = f"https://www.omdbapi.com/?i={IMDB_ID}&apikey={API_KEY}"

        # Make the API request
        response = requests.get(url)

        # Check if the request was successful
        if response.status_code == 200:
            data = response.json()

            # Extract the poster link
            poster_link = data.get("Poster")
            if poster_link:
                # Write IMDB ID and poster link to the file
                output_file.write(f"{IMDB_ID},{poster_link}\n")
        else:
            print(
                f"Failed to retrieve data for IMDB ID {IMDB_ID}. Status code: {response.status_code}")
