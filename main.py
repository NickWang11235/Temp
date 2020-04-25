import requests, os, sys
from bs4 import BeautifulSoup
from win32com.client.gencache import EnsureDispatch as Dispatch

URL = "https://community.articulate.com/series/storyline-3"
HOME_URL = "https://community.articulate.com"
        

with requests.Session() as s:
    r = s.get(URL)
    html = BeautifulSoup(r.text, "html.parser")
    sections = html.find("div", {"class" : "post__body series__body"}).find_all("section", {"class" : "series__section"})
    message = Dispatch ("CDO.Message")
    message.CreateMHTMLBody (URL)
    stream = Dispatch (message.GetStream ())
    stream.SaveToFile ("main page.mht", 2)
    stream.Close ()
    for sec in sections:
        ftag = sec.find("h2")
        links = sec.find("nav").find("ol").find_all("li")
        fpath = ""
        if ftag is not None:
            fpath = ftag.string
        else:
            fpath = "Getting Started"
        os.mkdir(fpath)
        for link in links:
            u = link.find("a")["href"]
            fname = u.split("/")[len(u.split("/"))-1]
            message = Dispatch ("CDO.Message")
            message.CreateMHTMLBody (HOME_URL + u)
            stream = Dispatch (message.GetStream ())
            stream.SaveToFile (fpath + "/" + fname + ".mht", 2)
            stream.Close ()
