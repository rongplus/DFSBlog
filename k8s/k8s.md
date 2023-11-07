see pending service:
    - run :  minikube tunnel

 kubectl expose deployment nginx-deployment-1 --type=LoadBalancer --name=nginx1
kubectl scale deployment test-deployment --replicas=10
minikube service myweb --url
 - minikube start
 --- mysql ---
 - kubectl apply -f mysql-rc.yaml  #create mysql container
 - kubectl apply -f mysql-service.yaml #create mysql service pod
 - kubectl get service   # check status
 - kubectl get nodes
 - kubectl describe node node-name
 - kubectl get pods
 - kubectl describe pod mysql-dcr5z
 - kubectl scale rc mysql --replicas=3 # set replica 

 --- web ---
 - kubectl apply -f myweb2.yaml 
 - kubectl get services -o wide
 - kubectl get pods -o wide
 - kubectl expose deployment hello-web --type=LoadBalancer --name=helloweb-service
 - minikube tunnel


---------------------------考证版------------------------------
minikube start --driver=virtualbox --kubernetes-version=v1.27.4 --no-vtx-check
VMware
minikube start --driver=vmware