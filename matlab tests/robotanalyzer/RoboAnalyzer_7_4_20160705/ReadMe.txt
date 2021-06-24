Steps to add a new skeleton robot-

Step 1: Add an entry of your robot inside "DefaultRobot.xml". Add following line "<Robot Name="YourRobotName"/>" without double quotes inside "DefaultRobots" node in XML. Make sure the XML structure is correct.

Step 2: Create a XML file, inside "DefaultRobots" folder. The XML file must have name in the following way "DOF_YourRobotName_Skeleton.xml". As an example, for 3 DOF PRR robot, the file name must be "3_PRR_Skeleton.xml"

Step 3: Define XML file (You can take the help of existing XML file inside "DefaultRobots" folder). Don't forget to mention the value of "DOF" and "SelectedRobot" parameter inside XML.