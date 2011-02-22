import smtplib
from email.mime.text import MIMEText

def sendMail(content):
	smtpServerIp = "192.168.1.18"
	smtpServerPort = 25
	loginPassword = ""
	loginName = ""
	
	server = smtplib.SMTP(smtpServerIp, smtpServerPort)

	fromaddr = "abc@infortrend.com"
	toaddr = "Andy.Pan@infortrend.com"
	
	msg = MIMEText(content)
	msg['Subject'] = "new1"
	msg['From'] = fromaddr
	msg['To'] = toaddr
	
	# for SMTP server without authentication,
	# we do not need to login
	if loginPassword != "":
		server.login(loginName, loginPassword)
	#server.set_debuglevel(1)
	server.sendmail(fromaddr, toaddr, msg.as_string())
	server.quit()

sendMail("hi")
