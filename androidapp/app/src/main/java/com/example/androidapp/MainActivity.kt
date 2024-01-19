package com.example.androidapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.androidapp.ui.theme.AndroidAppTheme
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.io.OutputStream
import java.net.Socket

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            AndroidAppTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    Column(
                        modifier = Modifier.fillMaxSize(),
                        verticalArrangement = Arrangement.Center,
                        horizontalAlignment = Alignment.CenterHorizontally
                    ) {
                        Text(text = "Shutdown pc based on a single button press")
                        Button(onClick = { shutdown_pc("192.168.1.134") }) {
                            Text(text = "pc 1")
                        }
                        Button(onClick = { shutdown_pc("192.168.1.131") }) {
                            Text(text = "pc 2")
                        }
                    }
                }
            }
        }
    }
}

fun shutdown_pc(ip: String) {
    GlobalScope.launch(Dispatchers.IO) {
        try {
            val socket = Socket(ip, 27015)

            val outputStream: OutputStream = socket.getOutputStream()

            val to_send = "1"
            outputStream.write(to_send.toByteArray())

            socket.close()

        } catch (e: Exception) {
            println("error: ")
            e.printStackTrace()
        }
    }
}