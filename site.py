import requests
from bs4 import BeautifulSoup
import pandas as pd
import urllib.request


# send a GET request to the website
url = "https://www.imdb.com/search/title/?genres=action"
response = requests.get(url)

# parse the response using BeautifulSoup
soup = BeautifulSoup(response.text, "html.parser")

# find all the div elements that have class "lister-item mode-advanced"
movies = soup.find_all("div", class_="lister-item mode-advanced")

# create empty lists to store the data
titles = []
genres = []
links = []

# loop through each movie element
for movie in movies:
    # find the h3 element that contains the title and link
    header = movie.find("h3", class_="lister-item-header")
    # get the text of the title and append it to the titles list
    title = header.find("a").text
    titles.append(title)
    # get the href attribute of the link and append it to the links list
    link = header.find("a")["href"]
    print("=================", link, "=====================")
    links.append(link)
    # find the span element that contains the genre and get its text
    genre = movie.find("span", class_="genre").text
    # remove any extra spaces or newlines and append it to the genres list
    genre = genre.strip().replace("\n", "")
    genres.append(genre)


# create a dictionary of lists
data = {"title": titles, "genre": genres, "link": links}

# create a data frame from the dictionary
df = pd.DataFrame(data)

# print the first 5 rows of the data frame
print(df.head())

# filter the data frame by genre
df = df[df["genre"].str.contains("Action")]

# print the first 5 rows of the filtered data frame
print(df.head())


for index, row in df.iterrows():
    # get the title and link of each movie
    title = row["title"]
    link = row["link"]
    # create a file name based on the title
    file_name = title + ".mp4"
    print(title, link, file_name)
    # download the file from the link and save it with the file name
    #urllib.request.urlretrieve(link, file_name)
