# Exercise: Create resources by using the Microsoft .NET SDK v3

In this exercise you create a console app to perform the following operations in Azure Cosmos DB:

## Connect to an Azure Cosmos DB account
    Create a database
    Create a container
    Prerequisites
    An Azure account with an active subscription. If you don't already have one, you can sign up for a free trial at https://azure.com/free.

Visual Studio Code on one of the supported platforms.

.NET 6 is the target framework for the exercise.

The C# extension for Visual Studio Code.

## Setting up
Perform the following actions to prepare Azure, and your local environment, for the exercise.

## Connecting to Azure
Start Visual Studio Code and open a terminal window by selecting Terminal from the top application bar, then choosing New Terminal.

Sign in to Azure by using the following command. A browser window should open letting you choose which account to sign in with.


Copy
<code>
az login
Create resources in Azure
Create a resource group for the resources needed for this exercise. Replace <myLocation> with a region near you.
</code>

Copy
<code>
az group create --location <myLocation> --name az204-cosmos-rg
</code>

Create the Azure Cosmos DB account. Replace <myCosmosDBacct> with a unique name to identify your Azure Cosmos DB account. The name can only contain lowercase letters, numbers, and the hyphen (-) character. It must be between 3-31 characters in length. This command takes a few minutes to complete.


Copy
<code>
az cosmosdb create --name <myCosmosDBacct> --resource-group az204-cosmos-rg
</code>

Record the documentEndpoint shown in the JSON response, it's used later in the exercise.

Retrieve the primary key for the account by using the following command. Record the primaryMasterKey from the command results it will be used in the code.


Copy
        # Retrieve the primary key
<code>az cosmosdb keys list --name <myCosmosDBacct> --resource-group az204-cosmos-rg</code>

## Set up the console application
Now that the needed resources are deployed to Azure the next step is to set up the console application using the same terminal window in Visual Studio Code.

Create a folder for the project and change in to the folder.


Copy
<code>
md az204-cosmos
cd az204-cosmos
Create the .NET console app.
</code>

Copy
<code>
dotnet new console
</code>

Open the current folder in Visual Studio Code using the following command. The -r option opens the folder without launching a new Visual Studio Code window.


Copy
<code>
code . -r
</code>

Select the Program.cs file in the Explorer pane to open the file in the editor.


## Build the console app
It's time to start adding the packages and code to the project.

### Add packages and using statements
Open the terminal in Visual Studio Code and use the following command to add the Microsoft.Azure.Cosmos package to the project.


Copy
<code>
dotnet add package Microsoft.Azure.Cosmos
Delete any existing code in the Program.cs file and add the using Microsoft.Azure.Cosmos statement.
</code>

C#

Copy
<code>
using Microsoft.Azure.Cosmos;
</code>


# Add code to connect to an Azure Cosmos DB account
Add the following code snippet after the using statement. The code snippet adds constants and variables into the class and adds some error checking. Be sure to replace the placeholder values for EndpointUri and PrimaryKey following the directions in the code comments.

### Run the application
Save your work and, in a terminal in Visual Studio Code, run the dotnet build command to check for any errors. If the build is successful run the dotnet run command. The console displays the following messages.

Copy
<code>
Beginning operations...

Created Database: az204Database

Created Container: az204Container

End of program, press any key to exit.
</code>

Verify the results by opening the Azure portal, navigating to your Azure Cosmos DB resource, and use the Data Explorer to view the database and container.

Clean up Azure resources
You can now safely delete the az204-cosmos-rg resource group from your account by running the following command.

Copy
<code>az group delete --name az204-cosmos-rg --no-wait</code>


