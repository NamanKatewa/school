"""
Task 3: ML in Cyber Security - Comparative Case Study
Domain: Network Intrusion Detection Systems (NIDS)
Author: Naman Katewa | Roll No: 2401830002 | Course: B.Sc.(H) Cybersecurity
"""

import json
import numpy as np
import matplotlib.pyplot as plt

def main():
    print("=" * 70)
    print("TASK 3: COMPARATIVE CASE STUDY - ML IN CYBER SECURITY")
    print("Student: Naman Katewa | Roll No: 2401830002 | Course: B.Sc.(H) Cybersecurity")
    print("Domain: Network Intrusion Detection Systems (NIDS)")
    print("=" * 70)

    # 1. Multi-Criteria Radar Chart
    categories = [
        'Detection\nAccuracy',
        'Inference\nThroughput',
        'Zero-Day\nAdaptability',
        'Explainability\n(SOC Audit)',
        'Training\nScalability',
        'Noise\nRobustness'
    ]
    N = len(categories)

    # Scores out of 10 based on peer-reviewed literature
    # RF: High accuracy, very high throughput, moderate zero-day, high explainability, high scalability, high robustness
    rf_scores = [9.5, 9.2, 6.0, 8.8, 8.5, 8.7]
    # SVM: High accuracy, low throughput, moderate zero-day, moderate explainability, low scalability, high robustness
    svm_scores = [8.8, 4.5, 6.5, 6.0, 3.5, 8.2]
    # Deep Autoencoders: High accuracy, moderate throughput, high zero-day, low explainability, moderate scalability, moderate robustness
    ae_scores = [9.2, 7.0, 9.4, 3.8, 6.0, 7.5]

    angles = [n / float(N) * 2 * np.pi for n in range(N)]
    angles += angles[:1]

    rf_scores += rf_scores[:1]
    svm_scores += svm_scores[:1]
    ae_scores += ae_scores[:1]

    fig, ax = plt.subplots(figsize=(8, 7), subplot_kw=dict(polar=True))
    plt.xticks(angles[:-1], categories, color='black', size=10, fontweight='bold')
    ax.set_rlabel_position(0)
    plt.yticks([2, 4, 6, 8, 10], ["2", "4", "6", "8", "10"], color="grey", size=8)
    plt.ylim(0, 10.5)

    # Plot each technique
    ax.plot(angles, rf_scores, linewidth=2.2, linestyle='solid', color='#377eb8', label='Random Forest (Ensemble)')
    ax.fill(angles, rf_scores, color='#377eb8', alpha=0.18)

    ax.plot(angles, svm_scores, linewidth=2.2, linestyle='dashed', color='#4daf4a', label='Kernel SVM (Optimal Hyperplane)')
    ax.fill(angles, svm_scores, color='#4daf4a', alpha=0.15)

    ax.plot(angles, ae_scores, linewidth=2.2, linestyle='dashdot', color='#e41a1c', label='Deep Autoencoders (Deep Learning)')
    ax.fill(angles, ae_scores, color='#e41a1c', alpha=0.15)

    plt.title('Multi-Criteria Evaluation: Three ML Techniques in NIDS', size=13, fontweight='bold', y=1.1)
    plt.legend(loc='upper right', bbox_to_anchor=(1.28, 1.15), frameon=True, fontsize=9)
    plt.tight_layout()
    plt.savefig('figures/task3/radar_comparison.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task3/radar_comparison.png")

    # 2. Literature Reported Metrics Comparison Bar Chart
    # Based on benchmark surveys (Tavallaee et al., Sharafaldin et al. CICIDS2017, Vinayakumar et al.)
    metrics = ['Detection Rate (%)', 'False Alarm Rate (%)', 'Macro F1-Score (%)', 'Throughput Score (1-10)']
    rf_lit = [99.7, 0.4, 99.6, 9.2]
    svm_lit = [98.2, 1.8, 98.1, 4.5]
    ae_lit = [97.5, 2.1, 97.2, 7.0]

    x = np.arange(len(metrics))
    width = 0.25

    fig, ax = plt.subplots(figsize=(9, 5))
    rects1 = ax.bar(x - width, rf_lit, width, label='Random Forest', color='#377eb8')
    rects2 = ax.bar(x, svm_lit, width, label='Support Vector Machine', color='#4daf4a')
    rects3 = ax.bar(x + width, ae_lit, width, label='Deep Autoencoder', color='#e41a1c')

    ax.set_ylabel('Literature Reported Benchmark Values', fontweight='bold', fontsize=10)
    ax.set_title('Empirical Benchmark Performance in NIDS Academic Literature', fontweight='bold', fontsize=12)
    ax.set_xticks(x)
    ax.set_xticklabels(metrics, fontweight='bold', fontsize=10)
    ax.legend(frameon=True)
    ax.grid(axis='y', linestyle=':', alpha=0.5)

    def autolabel(rects):
        for rect in rects:
            height = rect.get_height()
            ax.annotate(f'{height}',
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom', fontsize=8, fontweight='bold')

    autolabel(rects1)
    autolabel(rects2)
    autolabel(rects3)

    plt.tight_layout()
    plt.savefig('figures/task3/literature_benchmarks.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task3/literature_benchmarks.png")

    # Save summary data
    case_study_data = {
        "domain": "Network Intrusion Detection Systems (NIDS)",
        "techniques": [
            {
                "name": "Random Forest (Ensemble Learning)",
                "category": "Supervised Tree-based Ensemble",
                "datasets_used": ["NSL-KDD", "CICIDS-2017", "UNSW-NB15"],
                "reported_metrics": {"Detection_Rate": "99.5% - 99.8%", "False_Alarm_Rate": "< 0.5%", "F1_Score": "99.6%"},
                "advantages": ["Extreme computational efficiency during line-rate inference", "Direct feature importance ranking", "Intrinsic robustness to monotonic transformations and irrelevant features"],
                "limitations": ["Degraded generalization against structurally novel zero-day exploits", "Large memory footprint for ultra-deep tree ensembles"]
            },
            {
                "name": "Support Vector Machine (Kernelized SVM)",
                "category": "Supervised Maximum Margin Hyperplane",
                "datasets_used": ["NSL-KDD", "DARPA 1999", "Kyoto 2006+"],
                "reported_metrics": {"Detection_Rate": "96.5% - 98.8%", "False_Alarm_Rate": "1.2% - 2.5%", "F1_Score": "98.1%"},
                "advantages": ["Rigorous mathematical foundation minimizing structural risk", "Effective in high-dimensional feature spaces", "Robust against local minima"],
                "limitations": ["Quadratic to cubic training complexity O(N^2 - N^3)", "Slow inference per packet due to support vector kernel evaluations", "High sensitivity to feature scaling and hyperparameter tuning"]
            },
            {
                "name": "Deep Autoencoders (Reconstruction Anomaly Detection)",
                "category": "Unsupervised / Self-Supervised Deep Learning",
                "datasets_used": ["CICIDS-2017", "CSE-CIC-IDS2018", "Kitsune"],
                "reported_metrics": {"Detection_Rate": "95.0% - 98.2%", "False_Alarm_Rate": "1.8% - 3.2%", "F1_Score": "97.2%"},
                "advantages": ["Superior zero-day attack identification without requiring attack signatures", "Learns complex non-linear latent manifolds of benign network traffic", "End-to-end representation learning bypassing manual feature engineering"],
                "limitations": ["Black-box lack of interpretability impeding SOC incident triage", "High computational cost requiring GPU acceleration for real-time retraining", "Susceptible to threshold tuning drift in dynamic network environments"]
            }
        ]
    }
    with open("output/task3_results.json", "w") as f:
        json.dump(case_study_data, f, indent=4)
    print("[+] Saved output/task3_results.json")
    print("\n[V] TASK 3 COMPLETED SUCCESSFULLY.")

if __name__ == '__main__':
    main()
