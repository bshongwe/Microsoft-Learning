using Azure.Storage.Blobs;
using Azure.Storage.Blobs.Models;
using System;
using System.Threading.Tasks;

class Program
{
    static async Task Main()
    {
        Console.WriteLine("Azure Blob Storage exercise\n");

        // Run the examples asynchronously, wait for the results before proceeding
        await ProcessAsync();

        Console.WriteLine("Press enter to exit the sample application.");
        Console.ReadLine();
    }

    static async Task ProcessAsync()
    {
        // Copy the connection string from the portal in the variable below.
        string storageConnectionString = "CONNECTION STRING";

        // Create a client that can authenticate with a connection string
        BlobServiceClient blobServiceClient = new BlobServiceClient(storageConnectionString);

        // Example code: Create a container and upload a blob
        string containerName = "mycontainer";
        string blobName = "myblob.txt";
        string content = "Hello, Azure Blob Storage!";

        BlobContainerClient containerClient = blobServiceClient.GetBlobContainerClient(containerName);
        await containerClient.CreateIfNotExistsAsync();

        BlobClient blobClient = containerClient.GetBlobClient(blobName);
        await blobClient.UploadTextAsync(content);

        Console.WriteLine("Blob uploaded successfully!");

        // Example code: Download the blob
        BlobDownloadInfo download = await blobClient.DownloadAsync();
        string downloadedContent = await download.Content.ReadAsStringAsync();

        Console.WriteLine("Downloaded content:");
        Console.WriteLine(downloadedContent);

        // Example code: Delete the blob and container
        await blobClient.DeleteAsync();
        await containerClient.DeleteAsync();

        Console.WriteLine("Blob and container deleted successfully!");
    }
}
