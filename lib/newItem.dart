import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

class NewItemWidget extends StatefulWidget {
  NewItemWidget({Key key}) : super(key: key);
  @override
  _ItemState createState() => new _ItemState();
}

class _ItemState extends State<NewItemWidget> {

  void addData(String meal, String restName) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> mealList = prefs.getStringList("mealListKey");
    mealList.add(meal);
    prefs.setStringList("mealListKey", mealList);
  }
  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        title: new Text("New Meal!"),
      ),
      body: Center(
        child: Column(
          children: <Widget>[
            buildCard(),
            Padding(
              padding: EdgeInsets.all(10),
            ),
            //Checkbox(),
          ],
        ),
      ),
    );
  }

  Widget buildCard() {
    return Card(
        margin: EdgeInsets.all(10),
        child: Padding(
          padding: EdgeInsets.all(20),
          child: Column(
            children: <Widget>[
              Text("Enter the meal that you ate"),
              TextField(),
              Padding(
                padding: EdgeInsets.all(10),
              ),
              Text("What Restaurant did you go to?"),
              TextField(),
              Padding(
                padding: EdgeInsets.all(10),
              ),
              //Text("Select the cat of food"),
              FlatButton(
                child: Text(
                  "Save Data",
                  style: TextStyle(color: Colors.white),
                ),
                onPressed: () {},
                color: Colors.red,
              ),
            ],
          ),
        ));
  }
}
