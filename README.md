The "MNIST_binary_classification" is the folder containing binary classification model design.
The "matrix" folder contains matrix related files.
The "neuron" folder contains neuron related files.
The "display" folder contains functions for creating some GtkWidget objects.
Use "gcc train.c ../matrix/*.c ../neuron/*.c -I include/ -o train.out -lm" to compile, and "./train.out" to view the training.
For evaluating, install "VcXsrv" to install an X-server, and run "sudo apt install libgtk-3-dev -y" to install the GTK library.
Use "gcc evaluate.c ../display/*.c ../matrix/*.c ../neuron/*.c -I include/ `pkg-config --cflags --libs gtk+-3.0` -o evaluate.out -lm" to evaluate the model.
After running "./evaluate.out", draw on the drawing area by dragging the mouse.
For accuary reasons, draw the image around the center, and give the pixels high activations.
Press "Predict" to see the predictions.
Press "Refresh" to clear the drawing area.
