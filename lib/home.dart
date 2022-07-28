import 'dart:async';
import 'dart:ui';

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:firebase_messaging/firebase_messaging.dart';
import 'package:flutter/services.dart';

class Home extends StatefulWidget {
  const Home({Key? key}) : super(key: key);

  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {
  final databaseReference = FirebaseDatabase.instance.ref('123');
  updateFcm() {
    FirebaseMessaging.instance.getToken().then((value) {
      databaseReference.child('').update({"fcm": "$value"});
      databaseReference.child('').update({"status": "false"});
    });
  }

  @override
  void initState() {
    updateFcm();
    super.initState();
  }

  updateBuilder() {
    return databaseReference.child('').get().then((value) => value.value);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text("Electric Bike Status"),
          centerTitle: true,
          backgroundColor: Colors.black,
        ),
        backgroundColor: Colors.black,
        body: StreamBuilder(
            stream: databaseReference.child('status').onValue,
            builder: (context, AsyncSnapshot<DatabaseEvent> snapshot) {
              if (snapshot.hasData) {
                final map = snapshot.data!.snapshot.value;
                return Center(
                    child: Container(
                        width: 200,
                        height: 80,
                        decoration: BoxDecoration(
                          color: map == "true" ? Colors.green : Colors.red,
                          boxShadow: [
                            BoxShadow(
                              color: map == "true" ? Colors.green : Colors.red,
                              offset: Offset(0, 0),
                              blurRadius: 36,
                              spreadRadius: 16,
                            )
                          ],
                          borderRadius: BorderRadius.circular(30),
                        ),
                        child: Center(
                          child: Text(
                            '${map == "true" ? "Stand Up" : "Stand Down"}',
                            style: TextStyle(color: Colors.white, fontSize: 22),
                          ),
                        )));
              } else if (snapshot.hasError) {
                return Center(child: Text(snapshot.error.toString()));
              } else {
                return Center(child: CircularProgressIndicator());
              }
            }));
  }
}
