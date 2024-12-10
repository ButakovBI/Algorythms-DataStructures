import json
import sys

from calculator import Calculator
from services.clickhouse import Clickhouse
from services.database_server import DatabaseServer
from services.elasticsearch import ElasticSearch
from services.kafka import Kafka
from services.processor import Processor
from services.scanner import Scanner
from services.server import Server
from services.synchronizer import Synchronizer


def main(config_file: str):
    with open(config_file, 'r') as f:
        config = json.load(f)

    registered_services = {
        "kafka": Kafka,
        "elasticsearch": ElasticSearch,
        "processor": Processor,
        "server": Server,
        "database_server": DatabaseServer,
        "clickhouse": Clickhouse,
        "synchronizer": Synchronizer,
        "scanner": Scanner
    }

    services_parameters = {
        "agents": 13450,
        "storage": 4.78,
        "traffic": 56.3,
        "mail_traffic": 12.4,
        "distributed": False,
        "nodes": 8
    }

    calculator = Calculator(config, registered_services, services_parameters)

    all_configs = calculator.get_all_configs()
    with open("output_config.json", 'w') as f:
        json.dump(all_configs, f, indent=4)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print('Ошибка: нужно передать путь к конфигурационному файлу.')
    else:
        config_path = sys.argv[1]
        main(config_path)
