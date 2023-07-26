# Perform common operations with the Event Hubs client library

This unit contains examples of common operations you can perform with the Event Hubs client library (Azure.Messaging.EventHubs) to interact with an Event Hubs.

## Inspect Event Hubs
    Many Event Hubs operations take place within the scope of a specific partition. Because partitions are owned by the Event Hubs, their names are assigned at the time of creation. To understand what partitions are available, you query the Event Hubs using one of the Event Hubs clients. For illustration, the EventHubProducerClient is demonstrated in these examples, but the concept and form are common across clients.

## Publish events to Event Hubs
    In order to publish events, you need to create an EventHubProducerClient. Producers publish events in batches and may request a specific partition, or allow the Event Hubs service to decide which partition events should be published to. We recommended using automatic routing when the publishing of events needs to be highly available or when event data should be distributed evenly among the partitions. Our example takes advantage of automatic routing.

## Read events from an Event Hubs
    In order to read events from an Event Hubs, you need to create an EventHubConsumerClient for a given consumer group. When an Event Hubs is created, it provides a default consumer group that can be used to get started with exploring Event Hubs. In our example, we'll focus on reading all events that have been published to the Event Hubs using an iterator.

 Note

It is important to note that this approach to consuming is intended to improve the experience of exploring the Event Hubs client library and prototyping. It is recommended that it not be used in production scenarios. For production use, we recommend using the Event Processor Client, as it provides a more robust and performant experience.

## Read events from an Event Hubs partition
    To read from a specific partition, the consumer needs to specify where in the event stream to begin receiving events; in our example, we focus on reading all published events for the first partition of the Event Hubs.

## Process events using an Event Processor client
    For most production scenarios, it's recommended that the EventProcessorClient be used for reading and processing events. Since the EventProcessorClient has a dependency on Azure Storage blobs for persistence of its state, you need to provide a BlobContainerClient for the processor, which has been configured for the storage account and container that should be used.

