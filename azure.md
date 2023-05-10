ssh -i C:\Users\huang\Downloads\ubuntu-spark_key.pem azureuser@20.55.61.115



Go to %UserProfile%\.ssh
Copy and paste id_rsa, rename it to something else [example]
Open the renamed file [example] and replace the key with your own private key
cd to that directory
Enter your passphrase after issuing: ssh -i example example@127.0.0.1
 - ssh -i example.pem azureuser@4.227.145.213