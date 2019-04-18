import 'package:flutter/material.dart';
import 'package:location/location.dart';
import 'newItem.dart';
import 'dart:async';
import 'dart:convert';
import 'package:http/http.dart' as http;

//Class for json data
class Post {
  final int userId;
  final int id;
  final String title;
  final String body;

  Post({this.userId, this.id, this.title, this.body});

  factory Post.fromJson(Map<String, dynamic> json) {
    return Post(
      userId: json['userId'],
      id: json['id'],
      title: json['title'],
      body: json['body'],
    );
  }
}

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Food Recommendation',
      theme: ThemeData(
        primarySwatch: Colors.red,
      ),
      home: MyHomePage(title: 'Food Recommendation'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);
  final String title;
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  String lat = "Latitude: NULL",
      longitude = "Longitude: NULL",
      speed = "Speed: ";
  Location _location = new Location();

  //fetches data from json and places into POST
  Future<Post> fetchPost() async {
    final response =
        await http.get('https://jsonplaceholder.typicode.com/posts/1');
    if (response.statusCode == 200) {
      // If the call to the server was successful, parse the JSON
      return Post.fromJson(json.decode(response.body));
    } else {
      // If that call was not successful, throw an error.
      throw Exception('Failed to load post');
    }
  }

  //refreshes the users current location
  void refreshData() async {
    LocationData userLocation;
    userLocation = await _location.getLocation();
    print(userLocation.latitude);
    print(userLocation.longitude);
    //lat = userLocation.latitude.toString();
    setState(() {
      lat = "Latitude: " + userLocation.latitude.toString();
      longitude = "Longitude: " + userLocation.longitude.toString();
      speed = "Speed: " + userLocation.speed.toString();
      fetchPost();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          //mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Card(
                child: Padding(
              padding: EdgeInsets.all(20),
              child: Column(
                children: <Widget>[
                  Text(
                    "Top Recommendation",
                    style: TextStyle(fontSize: 25),
                  ),
                  Divider(),
                  recoTextWidget(),
                ],
              ),
            )),
            FlatButton(
              child: Text(
                "Refresh Data",
                style: TextStyle(color: Colors.white),
              ),
              onPressed: () {
                refreshData();
              },
              color: Colors.red,
            ),
            Text(lat),
            Text(longitude),
            Text(speed),
            FutureBuilder<Post>(
              future: fetchPost(),
              builder: (context, snapshot) {
                if (snapshot.hasData) {
                  return Text(snapshot.data.body);
                } else if (snapshot.hasError) {
                  return Text("${snapshot.error}");
                }
                // By default, show a loading spinner
                return CircularProgressIndicator();
              },
            ),
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.push(
            context,
            MaterialPageRoute(builder: (context) => NewItemWidget()),
          );
        },
        tooltip: 'New Meal',
        child: Icon(Icons.add),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }

  Widget recoTextWidget() {
    return Column(
      children: <Widget>[
        Text("1. INSERT HERE"),
        Divider(),
        Text("2. INSERT HERE"),
        Divider(),
        Text("3. INSERT HERE"),
        Divider(),
        Text("4. INSERT HERE"),
        Divider(),
        Text("5. INSERT HERE"),
      ],
    );
  }
}
