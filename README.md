# LumoHacks-2016-TAACC

# Problem Statement: 

-During mastectomy(surgery to remove malign breast tumor), the doctors will examine the lymph nodes in the armpit to check whether or not metastasis has happened (cancer spread to the lymphnodes)

-If the surgeons suspect that cancer has in fact spread to the lymphnodes, then the surgeons will remove the lymph node on the operating table. 

-Doing this will put the patient at risk for lymthadema, which causes swelling of the arms (increase arm volume), and decrease in arm mobility. 
Early detection for lymthadema can greatly increase chances of succesful treatment. 

-Unfortunately, there is a lack of early detection methods and convenient means for the patient to measure arm functionality. We aim to make it easy and convenient for them to do tests for arm mobility and record their data so that they can send it to their practitioners, to assist with remote diagnosis as well as support physicians by providing them with more data. 

# Pebble: 

-Created an App with clean and clear text UI that takes data from accelerometer for position and compass for angle. 

-Pings the phone, sends data to companion android app (or pebble mobile app via pebblekitJS), receives ack from the phone and vibrates to let the the patient/user to know that it is time to move to a different position. 


# Phone (work in progress):

-Simple UI that displays instructions. The instruction will change when it receives a ping from the pebble app. and then it will send an ack. It will hopefully be extended to store the data, perform numerical computation to determine some "quantity" for arm functionality, store the data and have some means within the app to send this to the practitioner. 

