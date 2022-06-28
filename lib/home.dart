import 'dart:async';

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:firebase_messaging/firebase_messaging.dart';

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
      databaseReference.child('').update({"status": "true"});
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
        body: StreamBuilder(
            stream: databaseReference.child('status').onValue,
            builder: (context, AsyncSnapshot<DatabaseEvent> snapshot) {
              if (snapshot.hasData) {
                final map = snapshot.data!.snapshot.value;
                return Center(child: Text('${map}'));
              } else if (snapshot.hasError) {
                return Center(child: Text(snapshot.error.toString()));
              } else {
                return Center(child: CircularProgressIndicator());
              }
            }));
  }
}
