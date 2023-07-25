# Microsoft-Learning
    My Microsoft Certification Learning Progress
    All files created, herein, were created by me based on the Microsoft-Learning online programme available at https://learn.microsoft.com/en-us/training
    Transcript link: https://learn.microsoft.com/en-us/users/ernestbhekizweshongwe-0897/transcript/7k212cgee8mp92p

## Azure Fundamentals: Describe Azure architecture and services

    Beginner
    Administrator
    Developer
    DevOps Engineer
    Solution Architect

## Azure
The Microsoft Azure Fundamentals training is composed of three learning paths: Microsoft Azure Fundamentals: Describe cloud concepts, Describe Azure architecture and services, and Describe Azure management and governance. Microsoft Azure Fundamentals: Azure architecture and services is the second learning path in the Microsoft Azure Fundamentals course. This learning path explores Microsoft Azure, its architecture, and some of the most commonly used services and resources.

This learning path helps prepare you for Exam AZ-900: Microsoft Azure Fundamentals.

### Prerequisites
Basic familiarity with IT terms and concepts

## Azure Cloud Shell

This module requires a sandbox to complete. A sandbox gives you access to Azure resources. Your Azure subscription will not be charged. The sandbox may only be used to complete training on Microsoft Learn. Use for any other reason is prohibited, and may result in permanent loss of access to the sandbox.

Microsoft provides this lab experience and related content for educational purposes. All presented information is owned by Microsoft and intended solely for learning about the covered products and services in this Microsoft Learn module.

### Exercise - Configure network access
This module requires a sandbox to complete.
A sandbox gives you access to free resources. Your personal subscription will not be charged. The sandbox may only be used to complete training on Microsoft Learn. Use for any other reason is prohibited, and may result in permanent loss of access to the sandbox.
Microsoft provides this lab experience and related content for educational purposes. All presented information is owned by Microsoft and intended solely for learning about the covered products and services in this Microsoft Learn module.

In this exercise, you'll configure the access to the virtual machine (VM) you created earlier in this module. The Microsoft Learn sandbox should still be running. If the sandbox timed out, you'll need to redo the previous exercise (Exercise - Create an Azure virtual machine).

Right now, the VM you created and installed Nginx on isn't accessible from the internet. You'll create a network security group that changes that by allowing inbound HTTP access on port 80.

#### Task 1: Access your web server
In this procedure, you get the IP address for your VM and attempt to access your web server's home page.

Run the following az vm list-ip-addresses command to get your VM's IP address and store the result as a Bash variable:

<code>
Azure CLI

Copy
IPADDRESS="$(az vm list-ip-addresses \
  --resource-group [sandbox resource group name] \
  --name my-vm \
  --query "[].virtualMachine.network.publicIpAddresses[*].ipAddress" \
  --output tsv)"

Run the following curl command to download the home page:

Bash

Copy
curl --connect-timeout 5 http://$IPADDRESS
</code>

The --connect-timeout argument specifies to allow up to five seconds for the connection to occur. After five seconds, you see an error message that states that the connection timed out:

<code>
Output

Copy
curl: (28) Connection timed out after 5001 milliseconds
</code>

This message means that the VM was not accessible within the timeout period.

As an optional step, try to access the web server from a browser:

Run the following to print your VM's IP address to the console:

<code>
Bash

Copy
echo $IPADDRESS
</code>

You see an IP address, for example, 23.102.42.235.

Copy the IP address that you see to the clipboard.

Open a new browser tab and go to your web server. After a few moments, you see that the connection isn't happening.

If you wait for the browser to time out, you'll see something like this:

Screenshot of a web browser showing an error message that says the connection timed out.

Keep this browser tab open for later.


### Task 2: List the current network security group rules
Your web server wasn't accessible. To find out why, let's examine your current NSG rules.

Run the following az network nsg list command to list the network security groups that are associated with your VM:

<code>
Azure CLI

Copy
az network nsg list \
  --resource-group [sandbox resource group name] \
  --query '[].name' \
  --output tsv
</code>

You see this:

<code>
Output

Copy
my-vmNSG
</code>

Every VM on Azure is associated with at least one network security group. In this case, Azure created an NSG for you called my-vmNSG.

Run the following az network nsg rule list command to list the rules associated with the NSG named my-vmNSG:

<code>
Azure CLI

Copy
az network nsg rule list \
  --resource-group [sandbox resource group name] \
  --nsg-name my-vmNSG
</code>

You see a large block of text in JSON format in the output. In the next step, you'll run a similar command that makes this output easier to read.

Run the az network nsg rule list command a second time. This time, use the --query argument to retrieve only the name, priority, affected ports, and access (Allow or Deny) for each rule. The --output argument formats the output as a table so that it's easy to read.

<code>
Azure CLI

Copy
az network nsg rule list \
  --resource-group [sandbox resource group name] \
  --nsg-name my-vmNSG \
  --query '[].{Name:name, Priority:priority, Port:destinationPortRange, Access:access}' \
  --output table
</code>

You see this:

<code>
Output

Copy
Name              Priority    Port    Access
-----------------  ----------  ------  --------
default-allow-ssh  1000        22      Allow
</code>

You see the default rule, default-allow-ssh. This rule allows inbound connections over port 22 (SSH). SSH (Secure Shell) is a protocol that's used on Linux to allow administrators to access the system remotely. The priority of this rule is 1000. Rules are processed in priority order, with lower numbers processed before higher numbers.

By default, a Linux VM's NSG allows network access only on port 22. This enables administrators to access the system. You need to also allow inbound connections on port 80, which allows access over HTTP.

### Task 3: Create the network security rule
Here, you create a network security rule that allows inbound access on port 80 (HTTP).

Run the following az network nsg rule create command to create a rule called allow-http that allows inbound access on port 80:

<code>
Azure CLI

Copy
az network nsg rule create \
  --resource-group [sandbox resource group name] \
  --nsg-name my-vmNSG \
  --name allow-http \
  --protocol tcp \
  --priority 100 \
  --destination-port-range 80 \
  --access Allow
</code>

For learning purposes, here you set the priority to 100. In this case, the priority doesn't matter. You would need to consider the priority if you had overlapping port ranges.

To verify the configuration, run az network nsg rule list to see the updated list of rules:

<code>
Azure CLI

Copy
az network nsg rule list \
  --resource-group [sandbox resource group name] \
  --nsg-name my-vmNSG \
  --query '[].{Name:name, Priority:priority, Port:destinationPortRange, Access:access}' \
  --output table
</code>

You see this both the default-allow-ssh rule and your new rule, allow-http:

<code>
Output

Copy
Name              Priority    Port    Access
-----------------  ----------  ------  --------
default-allow-ssh  1000        22      Allow
allow-http        100        80      Allow
</code>

### Task 4: Access your web server again
Now that you've configured network access to port 80, let's try to access the web server a second time.

 #### Note

After you update the NSG, it may take a few moments before the updated rules propagate. Retry the next step, with pauses between attempts, until you get the desired results.

Run the same curl command that you ran earlier:

<code>
Bash

Copy
curl --connect-timeout 5 http://$IPADDRESS
You see this:

HTML

Copy
<html><body><h2>Welcome to Azure! My name is my-vm.</h2></body></html>
</code>

As an optional step, refresh your browser tab that points to your web server.

You see this:

A screenshot of a web browser showing the home page from the web server. The home page displays a welcome message.

Nice work. In practice, you can create a standalone network security group that includes the inbound and outbound network access rules you need. If you have multiple VMs that serve the same purpose, you can assign that NSG to each VM at the time you create it. This technique enables you to control network access to multiple VMs under a single, central set of rules.

Clean up
The sandbox automatically cleans up your resources when you're finished with this module.

When you're working in your own subscription, it's a good idea at the end of a project to identify whether you still need the resources you created. Resources that you leave running can cost you money. You can delete resources individually or delete the resource group to delete the entire set of resources.


## Describe Azure storage services
Module
9 Units

    Beginner
    Administrator
    Developer
    DevOps Engineer
    Solution Architect

## Azure
This module introduces you to storage in Azure, including things such as different types of storage and how a distributed infrastructure can make your data more resilient.

Learning objectives
Upon completion of this module, you will be able to:

    Compare Azure storage services
    Describe storage tiers
    Describe redundancy options
    Describe storage account options and storage types
    Identify options for moving files, including AzCopy, Azure Storage Explorer, and Azure File Sync
    Describe migration options, including Azure Migrate and Azure Data Box


## Describe Azure storage accounts
A storage account provides a unique namespace for your Azure Storage data that's accessible from anywhere in the world over HTTP or HTTPS. Data in this account is secure, highly available, durable, and massively scalable.

When you create your storage account, you’ll start by picking the storage account type. The type of account determines the storage services and redundancy options and has an impact on the use cases. Below is a list of redundancy options that will be covered later in this module:

    Locally redundant storage (LRS)
    Geo-redundant storage (GRS)
    Read-access geo-redundant storage (RA-GRS)
    Zone-redundant storage (ZRS)
    Geo-zone-redundant storage (GZRS)
    Read-access geo-zone-redundant storage (RA-GZRS)

Type	Supported services	Redundancy Options	Usage
Standard general-purpose v2	Blob Storage (including Data Lake Storage), Queue Storage, Table Storage, and Azure Files	LRS, GRS, RA-GRS, ZRS, GZRS, RA-GZRS	Standard storage account type for blobs, file shares, queues, and tables. Recommended for most scenarios using Azure Storage. If you want support for network file system (NFS) in Azure Files, use the premium file shares account type.

Premium block blobs	Blob Storage (including Data Lake Storage)	LRS, ZRS	Premium storage account type for block blobs and append blobs. Recommended for scenarios with high transaction rates or that use smaller objects or require consistently low storage latency.
Premium file shares	Azure Files	LRS, ZRS	Premium storage account type for file shares only. Recommended for enterprise or high-performance scale applications. Use this account type if you want a storage account that supports both Server Message Block (SMB) and NFS file shares.

Premium page blobs	Page blobs only	LRS	Premium storage account type for page blobs only.
Storage account endpoints
One of the benefits of using an Azure Storage Account is having a unique namespace in Azure for your data. In order to do this, every storage account in Azure must have a unique-in-Azure account name. The combination of the account name and the Azure Storage service endpoint forms the endpoints for your storage account.

When naming your storage account, keep these rules in mind:

Storage account names must be between 3 and 24 characters in length and may contain numbers and lowercase letters only.
Your storage account name must be unique within Azure. No two storage accounts can have the same name. This supports the ability to have a unique, accessible namespace in Azure.
The following table shows the endpoint format for Azure Storage services.

### Storage service	Endpoint

<code>
Blob Storage	https://<storage-account-name>.blob.core.windows.net
Data Lake Storage Gen2	https://<storage-account-name>.dfs.core.windows.net
Azure Files	https://<storage-account-name>.file.core.windows.net
Queue Storage	https://<storage-account-name>.queue.core.windows.net
Table Storage	https://<storage-account-name>.table.core.windows.net
</storage-account-name>
</storage-account-name>
</code>


### Exercise - Create a storage blob

This module requires a sandbox to complete.
A sandbox gives you access to free resources. Your personal subscription will not be charged. The sandbox may only be used to complete training on Microsoft Learn. Use for any other reason is prohibited, and may result in permanent loss of access to the sandbox.
Microsoft provides this lab experience and related content for educational purposes. All presented information is owned by Microsoft and intended solely for learning about the covered products and services in this Microsoft Learn module.

Create a storage account
In this task, we will create a new storage account.

    Sign in to the Azure portal at https://portal.azure.com

    Select Create a resource.

    Under Categories, select Storage.

    Under Storage Account, select Create.

    On the Basics tab of the Create storage account blade, fill in the following information. Leave the defaults for everything else.

##### Setting	Value
Subscription	Concierge Subscription
Resource group	[sandbox resource group name]
Storage account name	create a unique storage account name
Location	default
Performance	Standard
Redundancy	Locally redundant storage (LRS)
Select Review + Create to review your storage account settings and allow Azure to validate the configuration.

    Once validated, select Create. Wait for the notification that the account was successfully created.

    Select Go to resource.

##### Work with blob storage
In this section, you'll create a Blob container and upload a picture

Under Data storage, select Containers.

Screenshot of the Container add section of a storage account.

Select + Container and complete the information.

Setting	Value
Name	Enter a name for the container
Public access level	Private (no anonymous access)
Select Create.

 #### Note

Step 4 will need an image. If you want to upload an image you already have on your computer, continue to Step 4. Otherwise, open a new browser window and search Bing for an image of a flower. Save the image to your computer.

Back in the Azure portal select the container you created, then select Upload.

Browse for the image file you want to upload. Select it and then select upload.

 Note

You can upload as many blobs as you like in this way. New blobs will be listed within the container.

Select the Blob (file) you just uploaded. You should be on the properties tab.

Copy the URL from the URL field and paste it into a new tab.

You should receive an error message similar to the following.

<code>
Copy
<Error>
  <Code>ResourceNotFound</Code>
  <Message>The specified resource does not exist. RequestId:4a4bd3d9-101e-005a-1a3e-84bd42000000 Time:2022-06-20T00:41:31.2482656Z</Message>
</Error>
</code>

Change the access level of your blob
Go back to the Azure portal

Select Change access level

Set the Public access level to Blob (anonymous read access for blobs only)

Screenshot with Change access level highlighted.

Select OK

Refresh the tab where you attempted to access the file earlier.

Congratulations - you've completed this exercise. You created a storage account, added a container to the storage account, and then uploaded blobs (files) to your container. Then you changed the access level so you could access your file from the internet.

Clean up
The sandbox automatically cleans up your resources when you're finished with this module.

When you're working in your own subscription, it's a good idea at the end of a project to identify whether you still need the resources you created. Resources that you leave running can cost you money. You can delete resources individually or delete the resource group to delete the entire set of resources.


## Create a client object

Working with any Azure resource using the SDK begins with creating a client object. In this section, you learn how to create client objects to interact with the three types of resources in the storage service: storage accounts, containers, and blobs.

When your application creates a client object, you pass a URI referencing the endpoint to the client constructor. You can construct the endpoint string manually, as shown in the examples in this article, or you can query for the endpoint at runtime using the Azure Storage management library.

The code samples in this unit use DefaultAzureCredential to authenticate to Azure via an Azure Active Directory (Azure AD) security principal. The authentication process includes obtaining an access token for authorization. This access token is passed as a credential when the client is instantiated, and the credential persists throughout the client lifetime. The Azure AD security principal requesting the token must be assigned an appropriate Azure RBAC role that grants access to blob data.

## Create a BlobServiceClient object
An authorized BlobServiceClient object allows your app to interact with resources at the storage account level. BlobServiceClient provides methods to retrieve and configure account properties, as well as list, create, and delete containers within the storage account. This client object is the starting point for interacting with resources in the storage account.

The following example shows how to create a BlobServiceClient object:

<code>
C#

Copy
using Azure.Identity;
using Azure.Storage.Blobs;

public BlobServiceClient GetBlobServiceClient(string accountName)
{
    BlobServiceClient client = new(
        new Uri($"https://{accountName}.blob.core.windows.net"),
        new DefaultAzureCredential());

    return client;
}
</code>

## Create a BlobContainerClient object
You can use a BlobServiceClient object to create a new BlobContainerClient object. A BlobContainerClient object allows you to interact with a specific container resource. BlobContainerClient provides methods to create, delete, or configure a container, and includes methods to list, upload, and delete the blobs within it.

The following example shows how to create a container client from a BlobServiceClient object to interact with a specific container resource:

<code>
C#

Copy
public BlobContainerClient GetBlobContainerClient(
    BlobServiceClient blobServiceClient,
    string containerName)
{
    // Create the container client using the service client object
    BlobContainerClient client = blobServiceClient.GetBlobContainerClient(containerName);
    return client;
}
</code>

If your work is narrowly scoped to a single container, you might choose to create a BlobContainerClient object directly without using BlobServiceClient.

<code>
C#

Copy
public BlobContainerClient GetBlobContainerClient(
    string accountName,
    string containerName,
    BlobClientOptions clientOptions)
{
    // Append the container name to the end of the URI
    BlobContainerClient client = new(
        new Uri($"https://{accountName}.blob.core.windows.net/{containerName}"),
        new DefaultAzureCredential(),
        clientOptions);

    return client;
}
</coe>

## Create a BlobClient object
To interact with a specific blob resource, create a BlobClient object from a service client or container client. A BlobClient object allows you to interact with a specific blob resource.

The following example shows how to create a blob client to interact with a specific blob resource:

<code>
C#

Copy
public BlobClient GetBlobClient(
    BlobServiceClient blobServiceClient,
    string containerName,
    string blobName)
{
    BlobClient client =
        blobServiceClient.GetBlobContainerClient(containerName).GetBlobClient(blobName);
    return client;
}
</code>

