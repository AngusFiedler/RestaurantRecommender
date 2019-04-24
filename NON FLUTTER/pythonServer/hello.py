from flask import Flask
from flask import request,abort,url_for
import json
import os

app = Flask(__name__, static_url_path='/static')


@app.route('/')
def home():
    return 'This is a Flask server for running Restaurant Recommender'

@app.route('/send')
def send():
    return "<a href=%s>file</a>" % url_for('static', filename='1.json')

@app.route('/foo', methods=['POST','GET']) 
def foo():
    if request.method == 'POST':
        #fo = open("test.txt", "w")
        #filebuffer = [request.data.decode("utf-8") ]
        #fo.writelines(filebuffer)
        #fo.close()
        command = "./a.out " + request.data.decode("utf-8")
        os.system(command)
        return request.data
    if not request.json:
        abort(400)
    return json.dumps(request.json)


if __name__ == '__main__':
    app.run()
