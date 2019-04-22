import 'dart:async';
import 'dart:convert';
import 'package:http/http.dart' as http;

//Class for json data
class Post {
  final String category;
  final String location;
  final double rating;
  final String restaurantName;

  Post({this.category, this.location, this.rating, this.restaurantName});

  factory Post.fromJson(Map<String, dynamic> json) {
    return Post(
      category: json['category'],
      location: json['location'],
      rating: json['rating'],
      restaurantName: json['name']
    );
  }

  Map toMap() {
    var map = new Map<String, dynamic>();
    map["category"] = category;
    map["location"] = location;
    map["rating"] = rating;
    map["restaurantname"] = restaurantName;
    return map;
  }
}
//Class that performs all json data actions

class JsonUtil {
  //test url: https://jsonplaceholder.typicode.com/posts/1
  String recieveURL = "https://api.myjson.com/bins/";
  String sendURL = "https://httpbin.org/ip";

  //retreives data from post
  Future<Post> fetchPost(String id) async {
    final response =
        await http.get(recieveURL+id);
    if (response.statusCode == 200) {
      // If the call to the server was successful, parse the JSON
      return Post.fromJson(json.decode(response.body));
    } else {
      // If that call was not successful, throw an error.
      throw Exception('Failed to load post');
    }
  }
  //Sends data to given URL
  Future<Post> createPost(String restaurantName) async {
    return http.post(sendURL, body: restaurantName).then((http.Response response) {
    final int statusCode = response.statusCode;
 
    if (statusCode < 200 || statusCode > 400 || json == null) {
      throw new Exception("Error while fetching data");
    }
    return Post.fromJson(json.decode(response.body));
  });
  }
}
