# ROS 2 familiarization tasks

This submission contains two parts: a customized publisher/subscriber pair, and a turtlesim node that draws a star shape.

## Part 1 — Custom Publisher/Subscriber Message

The standard ROS 2 talker/listener demo publishes "Hello World" over a topic. This version publishes a custom string message instead, while keeping the same publish-subscribe logic.

### Logic

- The **talker** node (`my_talker.py`) creates a publisher on a topic called `topic` using the `std_msgs/String` message type.
- A ROS 2 timer fires every 0.5 seconds, building a new `String` message and overwriting `msg.data` with custom text (`"JANA THE ENG, count: {i}"`, incrementing a counter each time) before publishing it.
- The **listener** node (`my_listener.py`) subscribes to the same topic name and message type. Whenever a message arrives, ROS automatically calls `listener_callback`, which prints whatever string it receives.
- The two nodes never talk to each other directly — they only agree on a shared topic name and message type, which is the core idea behind ROS 2's publish-subscribe communication pattern.

### Files
- `jana_talker.py` — publisher node with the customized message
- `jana_listener.py` — subscriber node that prints received messages

### How to run

Open two terminals.

**Terminal 1:**
```bash
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run py_pubsub talker
```

**Terminal 2:**
```bash
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run py_pubsub listener
```

### Screenshot — talker/listener output

<img width="683" height="502" alt="لقطة شاشة 2026-08-08 010205" src="https://github.com/user-attachments/assets/7b841777-8fc8-4f1d-8e9b-a9c9a215d6da" />


---

## Part 2 — Turtlesim Star

This node drives the turtlesim turtle to trace a 5-pointed star by publishing velocity commands to `/turtle1/cmd_vel`.

### Logic

The node is a simple **state machine** with two states, `forward` and `turn`:

- In the `forward` state, it publishes a constant forward velocity (`linear.x = 2.0`) for 2 seconds.
- It then switches to the `turn` state, publishing a constant angular velocity (`angular.z = 1.5708` rad/s, about 90°/sec) for 1.6 seconds — this rotates the turtle by 144°, which is the exterior angle needed to form the points of a 5-pointed star (`360° ÷ 5 × 2 = 144°`).
- After each turn, `side_count` increments. Once 5 segments have been drawn, the node publishes a zero-velocity message to stop the turtle and shuts itself down.
- A ROS 2 timer calls this logic every 0.1 seconds, continuously re-publishing the current state's velocity — Twist messages don't persist on their own, so the turtle stops moving if the node stops sending them.

### File
- `turtle_star.py`

### How to run

**Terminal 1:**
```bash
source /opt/ros/humble/setup.bash
ros2 run turtlesim turtlesim_node
```

**Terminal 2:**
```bash
source /opt/ros/humble/setup.bash
cd ~/turtle_scripts
python3 turtle_star.py
```

### Screenshot — resulting star shape

<img width="958" height="500" alt="لقطة شاشة 2026-08-08 023043" src="https://github.com/user-attachments/assets/2ca6c4b3-9274-4ddb-a9ab-3e900be28130" />


---

## Notes

- All scripts require ROS 2 Humble sourced (`source /opt/ros/humble/setup.bash`) before running.
- The turtlesim window must be open and running before the star script is executed, since it publishes to `/turtle1/cmd_vel` which only exists once `turtlesim_node` is active.
- Turn duration and speed in `turtle_star.py` can be adjusted (the `1.6` second turn duration and `1.5708` rad/s angular speed) to make the star's points sharper or more rounded.
