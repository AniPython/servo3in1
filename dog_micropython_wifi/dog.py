
from robot import Robot


class Dog(Robot):
    def __init__(self, servo_totals):
        super().__init__(servo_totals)

    def init(self, f, b):
        self._servo_pins[0] = f
        self._servo_pins[1] = b

        self.attachServos()
        self.setRestState(False)

    def setTrims(self, f, b):
        self._servo[0].SetTrim(f)
        self._servo[1].SetTrim(b)

    def home(self):
        print("home")
        if self.getRestState() == False:  # -- Go to rest position only if necessary
            homes = [90, 90]  # -- All the servos at rest position
            self.moveServos(500, homes)  # -- Move the servos in half a second
            self.detachServos()
            self.setRestState(True)

    def forward(self, steps=3, T=1000):
        print("forward")
        A = [30, 30]
        O = [0, 0]
        phase_diff = [0, 1.57]

        self.execute(A, O, T, phase_diff, steps)

    def backward(self, steps=3, T=1000):
        print("backward")
        A = [30, 30]
        O = [0, 0]
        phase_diff = [0, -1.57]

        self.execute(A, O, T, phase_diff, steps)
