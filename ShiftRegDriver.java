//package pl.zdanek.redeye.output.jni;

/**
 * Created by bartek on 27.10.14.
 */
public class ShiftRegDriver {

    static {
        System.loadLibrary("shiftreg");
    }

    private native void shiftOut(byte[] data, int length);

    public static void main(String[] argv) {
        byte[] byteArr = new byte[] {0, 1, 0, 1};
        new ShiftRegDriver().shiftOut(byteArr, byteArr.length);
    }
}

