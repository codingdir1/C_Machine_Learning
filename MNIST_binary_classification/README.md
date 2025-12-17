The "MNIST_binary_classification" is the folder containing binary classification model design.
Use "gcc train.c ../matrix/*.c ../neuron/*.c -I include/ -o train.out -lm" to compile, and "./train.out" to view the training.
For evaluating, install "VcXsrv" to install an X-server, and run "sudo apt install libgtk-3-dev -y" to install the GTK library.
Use "gcc evaluate.c ../matrix/*.c ../neuron/*.c ../display/*.c ./handlers/*.c  -I include/ `pkg-config --cflags --libs gtk+-3.0` -o evaluate.out -lm" to get a output file "evaluate.out".
After running "./evaluate.out", draw on the drawing area by dragging the mouse.
For accuary reasons, draw the image around the center, and give the pixels high activations.
Press "Predict" to see the predictions.
Press "Refresh" to clear the drawing area.
