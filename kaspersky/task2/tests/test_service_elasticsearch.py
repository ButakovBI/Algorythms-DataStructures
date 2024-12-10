from services.elasticsearch import ElasticSearch


def test_elasticsearch_not_distributed_two_k_agents():
    elasticsearch = ElasticSearch()
    elasticsearch.update_config(
        agents=2000,
        mail_traffic=300,
        distributed=False,
        nodes=5)
    config = elasticsearch.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == 0
    assert config["cpu"] == 3
    assert config["storage"] == 0.256


def test_elasticsearch_distributed_five_k_agents():
    elasticsearch = ElasticSearch()
    elasticsearch.update_config(
        agents=5000,
        mail_traffic=300,
        distributed=True,
        nodes=5)
    config = elasticsearch.get_config()
    assert config["replicas"] == 3
    assert config["memory"] == 0
    assert config["cpu"] == 3
    assert config["storage"] == 0.512


def test_elasticsearch_not_distributed_ten_k_agents():
    elasticsearch = ElasticSearch()
    elasticsearch.update_config(
        agents=10000,
        mail_traffic=300,
        distributed=False,
        nodes=5)
    config = elasticsearch.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == 0
    assert config["cpu"] == 3
    assert config["storage"] == 1
